#include "render_system.h"

#include "log/logger.h"

#include "utility/matrix.hpp"

RenderSystem::RenderSystem(GLFWwindow* window)
    : window(window)
    , bufferedShapes(/*static_cast<ShapeID>(IShape::Type::MAX_SHAPES), nullptr*/)
{
    this->InitializeOpenGL();

    this->textRenderer = std::make_unique<TextRenderer>();
    this->textRenderer->Load("fonts/Antonio-Bold.ttf", 24);

    this->vertexBuffer = new VertexBuffer(GLOBAL_VERTEX_BUFFER_SIZE);
    this->indexBuffer  = new IndexBuffer(GLOBAL_INDEX_BUFFER_SIZE);

    this->RegisterEventCallbacks();
}

RenderSystem::~RenderSystem()
{

    this->UnregisterEventCallbacks();

    for (size_t i = 0; i < this->bufferedShapes.size(); ++i)
    {
        delete this->bufferedShapes[i];
        this->bufferedShapes[i] = nullptr;
    }
    this->bufferedShapes.clear();

    for (auto& it : this->renderableGroups)
    {
        it.first.Delete();
        it.second.clear();
    }

    this->textRenderer.release();
    this->textRenderer = nullptr;

    // free global vertex and index buffer
    delete this->vertexBuffer;
    this->vertexBuffer = nullptr;

    delete this->indexBuffer;
    this->indexBuffer = nullptr;

    this->TerminateOpenGL();
}

void RenderSystem::PreUpdate(ecs::f32 dt)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderSystem::Update(ecs::f32 dt)
{
    // call renderers
    MaterialID    lastUsedMaterial    = INVALID_MATERIAL_ID;
    VertexArrayID lastUsedVertexArray = -1;

    for (auto& renderableGroup : this->renderableGroups)
    {

        // activate material, if different from current used
        if (renderableGroup.first.material.GetMaterialID() != lastUsedMaterial)
        {
            renderableGroup.first.material.Use();

            // Set active camera's view and projection matrix
            //            ((RenderableGroup)(renderableGroup.first))
            //                .material.SetViewProjectionTransform(
            //                    this->m_ActiveCamera->GetViewTransform(),
            //                    this->m_ActiveCamera->GetProjectionTransform());

            lastUsedMaterial = renderableGroup.first.material.GetMaterialID();
        }

        // activate vertex array, if different from current bound
        if (renderableGroup.first.vertexArray->id != lastUsedVertexArray)
        {
            // restore vertex attribute bindings for this group
            renderableGroup.first.vertexArray->Bind();

            lastUsedVertexArray = renderableGroup.first.vertexArray->id;
        }

        // render all renderables of current group
        for (const auto& renderable : renderableGroup.second)
        {
            // ignore disables renderables
            if (renderable.gameObject->IsActive() == false && renderable.material->GetIsActive() == true &&
                renderable.shape->GetIsActive() == true)
            {
                continue;
            }

            if (renderable.texture != nullptr)
            {
                renderable.texture->Apply();
                renderable.material->SetUniform1f(MIX_VALUE_UNIFORM_NAME, 0.0);
            }
            else
            {
                renderable.material->SetUniform1f(MIX_VALUE_UNIFORM_NAME, 1.0);
            }

            // apply material
            renderable.material->Apply();

            // Set model transform uniform
            const auto& transform = renderable.transform->GetTransform();
            renderable.material->SetModelTransform(transform);

            // draw shape
            if (renderable.shape->IsIndexed() == true)
            {
                // draw with indices
                glDrawElements(renderable.shape->GetRenderingMode(),
                               renderable.shape->GetIndexesCount(),
                               VERTEX_INDEX_DATA_TYPE,
                               (const GLvoid*)(renderable.shape->GetIndexDataIndex()));
            }
            else
            {
                // draw without indices
                glDrawArrays(renderable.shape->GetRenderingMode(),
                             0,
                             renderable.shape->GetRenderingMode() == GL_TRIANGLES
                                 ? renderable.shape->GetTrianglesCount()
                                 : renderable.shape->GetLinesCount());
            }

            if (renderable.texture != nullptr)
            {
                renderable.texture->Misapply();
            }
        }

        // Check for errors
        //        glGetLastError();
    }

    glBindVertexArray(0);
    glUseProgram(0);

    this->textRenderer->RenderText();
}

void RenderSystem::PostUpdate(ecs::f32 dt)
{
    glfwSwapBuffers(this->window);
    glfwPollEvents();
}

void RenderSystem::DrawText(const std::string& text, const Vector2f& position, const float scale, const Color color)
{
    this->textRenderer->AddText(text, position, scale, color);
}

void RenderSystem::InitializeOpenGL()
{

    glfwMakeContextCurrent(this->window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        LogError("Failed to initialize GLAD");
        return;
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
}

void RenderSystem::TerminateOpenGL()
{
    glUseProgram(0);
}

void RenderSystem::RegisterEventCallbacks()
{
    this->RegisterEventCallback(&RenderSystem::OnWindowResized);
    this->RegisterEventCallback(&RenderSystem::OnWindowMinimized);
    this->RegisterEventCallback(&RenderSystem::OnWindowRestored);

    this->RegisterEventCallback(&RenderSystem::OnGameObjectCreated);
    this->RegisterEventCallback(&RenderSystem::OnGameObjectDestroyed);
}

void RenderSystem::UnregisterEventCallbacks()
{
    this->UnregisterEventCallback(&RenderSystem::OnWindowResized);
    this->UnregisterEventCallback(&RenderSystem::OnWindowMinimized);
    this->UnregisterEventCallback(&RenderSystem::OnWindowRestored);

    this->UnregisterEventCallback(&RenderSystem::OnGameObjectCreated);
    this->UnregisterEventCallback(&RenderSystem::OnGameObjectDestroyed);
}

void RenderSystem::SetShapeBufferIndex(ShapeComponent* shapeComponent)
{
    assert(shapeComponent->GetShapeID() != static_cast<ShapeID>(IShape::Type::INVALID_SHAPE) &&
           "RenderSystem got Entity with invalid shape.");
    // FIXME: Rework work buffered shapes
    const auto it = std::find_if(this->bufferedShapes.begin(),
                                 this->bufferedShapes.end(),
                                 [&](const ShapeBufferIndex* bufferIndex)
                                 { return bufferIndex->GetShapeId() == shapeComponent->GetShapeID(); });
    if (it != this->bufferedShapes.end())
    {
        // set indices
        shapeComponent->SetShapeBufferIndex(**it);
        return;
    }

    // Shape is not buffered yet.
    ShapeBufferIndex* bufferIndex = new ShapeBufferIndex;
    this->bufferedShapes.push_back(bufferIndex);

    // bind global vertex buffer
    this->vertexBuffer->Bind();

    // buffer vertex position data
    {
        assert(shapeComponent->GetPositions() != nullptr && "Invalid shape. Shape has no vertex position data!");
        bufferIndex->positionDataIndex = this->vertexBuffer->BufferVertexData(
            shapeComponent->GetPositions(), VERTEX_POSITION_DATA_ELEMENT_SIZE * shapeComponent->GetVertexesCount());
    }

    // buffer vertex index data
    if (shapeComponent->GetIndexesCount() > 0 && shapeComponent->GetIndexes() != nullptr)
    {
        this->indexBuffer->Bind();
        {
            bufferIndex->indexDataIndex = this->indexBuffer->BufferIndexData(
                shapeComponent->GetIndexes(), VERTEX_INDEX_DATA_ELEMENT_SIZE * shapeComponent->GetIndexesCount());
        }
        this->indexBuffer->Unbind();
    }

    // buffer vertex normal data
    if (shapeComponent->GetNormals() != nullptr)
    {
        bufferIndex->normalDataIndex = this->vertexBuffer->BufferVertexData(
            shapeComponent->GetNormals(), VERTEX_NORMAL_DATA_ELEMENT_SIZE * shapeComponent->GetVertexesCount());
    }

    // buffer vertex uv data
    if (shapeComponent->GetTexCoords() != nullptr)
    {
        bufferIndex->texCoordDataIndex = this->vertexBuffer->BufferVertexData(
            shapeComponent->GetTexCoords(), VERTEX_TEXCOORD_DATA_ELEMENT_SIZE * shapeComponent->GetVertexesCount());
    }

    // buffer vertex color data
    if (shapeComponent->GetColors() != nullptr)
    {
        bufferIndex->colorDataIndex = this->vertexBuffer->BufferVertexData(
            shapeComponent->GetColors(), VERTEX_COLOR_DATA_ELEMENT_SIZE * shapeComponent->GetVertexesCount());
    }

    // unbind global vertex buffer
    this->vertexBuffer->Unbind();

    // set indices
    shapeComponent->SetShapeBufferIndex(*bufferIndex);
}

void RenderSystem::RegisterRenderable(ecs::IEntity*       entity,
                                      TransformComponent* transform,
                                      MaterialComponent*  material,
                                      ShapeComponent*     shape,
                                      TextureComponent*   texture)
{
    const RenderableGroupID RGID = this->CreateRenderableGroupID(material, shape);

    // check if there is already a group for this renderable
    for (const auto& it : this->renderableGroups)
    {
        if (it.first.groupID == RGID)
        {
            // place renderable in this group
            this->renderableGroups[RGID].push_back(Renderable(entity, transform, material, shape, texture));
            return;
        }
    }

    RenderableGroup renderableGroup(RGID, *material);

    renderableGroup.vertexArray->Bind();

    {
        // bind global vertex buffer
        this->vertexBuffer->Bind();

        // buffer vertex position data
        MaterialVertexAttributeLoc positionVertexAttribute = material->GetPositionVertexAttributeLocation();
        assert(positionVertexAttribute != INVALID_MATERIAL_VERTEX_ATTRIBUTE_LOC &&
               "Material of a renderable does not provide a position vertex "
               "attribute!");

        glVertexAttribPointer(positionVertexAttribute,
                              VERTEX_POSITION_DATA_ELEMENT_LEN,
                              VERTEX_POSITION_DATA_TYPE,
                              GL_FALSE,
                              0 /*3 * sizeof(float)*/,
                              (const GLvoid*)(shape->GetPositionDataIndex()));
        glEnableVertexAttribArray(positionVertexAttribute);

        // buffer vertex index data
        if (shape->GetIndexesCount() > 0 && shape->GetIndexes() != nullptr)
        {
            this->indexBuffer->Bind();
        }

        // buffer vertex normal data
        MaterialVertexAttributeLoc normalVertexAttribute = material->GetNormalVertexAttributeLocation();
        if (shape->GetNormals() != nullptr && normalVertexAttribute != INVALID_MATERIAL_VERTEX_ATTRIBUTE_LOC)
        {
            glVertexAttribPointer(normalVertexAttribute,
                                  VERTEX_NORMAL_DATA_ELEMENT_LEN,
                                  VERTEX_NORMAL_DATA_TYPE,
                                  GL_FALSE,
                                  0,
                                  (const GLvoid*)(shape->GetNormalDataIndex()));
            glEnableVertexAttribArray(normalVertexAttribute);
        }

        // buffer vertex uv data
        MaterialVertexAttributeLoc texCoordVertexAttribute = material->GetTexCoordVertexAttributeLocation();
        if (shape->GetTexCoords() != nullptr && texCoordVertexAttribute != INVALID_MATERIAL_VERTEX_ATTRIBUTE_LOC)
        {
            glVertexAttribPointer(texCoordVertexAttribute,
                                  VERTEX_TEXCOORD_DATA_ELEMENT_LEN,
                                  VERTEX_TEXCOORD_DATA_TYPE,
                                  GL_FALSE,
                                  0,
                                  (const GLvoid*)(shape->GetTexCoordDataIndex()));
            glEnableVertexAttribArray(texCoordVertexAttribute);
        }

        // buffer vertex color data
        MaterialVertexAttributeLoc colorVertexAttribute = material->GetColorVertexAttributeLocation();
        if (shape->GetColors() != nullptr && colorVertexAttribute != INVALID_MATERIAL_VERTEX_ATTRIBUTE_LOC)
        {
            glVertexAttribPointer(colorVertexAttribute,
                                  VERTEX_COLOR_DATA_ELEMENT_LEN,
                                  VERTEX_COLOR_DATA_TYPE,
                                  GL_FALSE,
                                  0,
                                  (const GLvoid*)(shape->GetColorDataIndex()));
            glEnableVertexAttribArray(colorVertexAttribute);
        }
    }

    renderableGroup.vertexArray->Unbind();

    this->vertexBuffer->Unbind();
    this->indexBuffer->Unbind();

    this->renderableGroups[renderableGroup].push_back(Renderable(entity, transform, material, shape, texture));
}

void RenderSystem::UnregisterRenderable(GameObjectId gameObjectId)
{
    for (auto& RG : this->renderableGroups)
    {
        for (RenderableList::iterator it = RG.second.begin(); it != RG.second.end(); ++it)
        {
            if (it->gameObject->GetEntityID() == gameObjectId)
            {
                RG.second.erase(it);
                return;
            }
        }
    }
}

void RenderSystem::OnWindowResized(const WindowResizedEvent* event)
{
    glViewport(0, 0, event->width, event->height);
}

void RenderSystem::OnWindowMinimized(const WindowMinimizedEvent* event) {}

void RenderSystem::OnWindowRestored(const WindowRestoredEvent* event) {}

void RenderSystem::OnGameObjectCreated(const GameObjectCreated* event)
{
    ecs::IEntity* entity = ecs::ecsEngine->GetEntityManager()->GetEntity(event->entityID);
    assert(entity != nullptr && "Failed to retrive entity by id!");

    TransformComponent* transformComponent = entity->GetComponent<TransformComponent>();
    MaterialComponent*  materialComponent  = entity->GetComponent<MaterialComponent>();
    ShapeComponent*     shapeComponent     = entity->GetComponent<ShapeComponent>();
    TextureComponent*   textureComponent   = entity->GetComponent<TextureComponent>();

    if (transformComponent == nullptr || materialComponent == nullptr || shapeComponent == nullptr)
    {
        return;
    }
    const auto lolkek = shapeComponent->GetShapeID();
    this->SetShapeBufferIndex(shapeComponent);
    this->RegisterRenderable(entity, transformComponent, materialComponent, shapeComponent, textureComponent);
}

void RenderSystem::OnGameObjectDestroyed(const GameObjectDestroyed* event)
{
    this->UnregisterRenderable(event->entityID);
}
