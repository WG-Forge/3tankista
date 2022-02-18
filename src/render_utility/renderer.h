#pragma once

#include "buffers.h"
#include "ishape.h"
#include "opengl.h"
#include "renderable.h"
#include "shape_buffer_index.h"

#include "ecs.h"

#include "components/shape_component.h"
#include "components/transform_component.h"

class Renderer
{
    using BufferedShapes = std::vector<ShapeBufferIndex*>;

public:
    Renderer();
    virtual ~Renderer();

    void Flush()
    {

        VertexArrayID lastUsedVertexArray = -1;

        for (auto& renderableGroup : this->renderableGroups)
        {
            // activate vertex array, if different from current bound
            if (renderableGroup.first.vertexArray->id != lastUsedVertexArray)
            {
                // restore vertex attribute bindings for this group
                renderableGroup.first.vertexArray->Bind();

                lastUsedVertexArray = renderableGroup.first.vertexArray->id;
            }
            /*
                        // activate material, if different from current used
                        if (renderableGroup.first.m_Material.GetMaterialID() !=
                            lastUsedMaterial)
                        {
                            renderableGroup.first.m_Material.Use();

                            // Set active camera's view and projection matrix
                            ((RenderableGroup)(renderableGroup.first))
                                .m_Material.SetViewProjectionTransform(
                                    this->m_ActiveCamera->GetViewTransform(),
                                    this->m_ActiveCamera->GetProjectionTransform());

                            lastUsedMaterial =
                                renderableGroup.first.m_Material.GetMaterialID();
                        }
            */
            // render all renderables of current group
            for (auto renderable : renderableGroup.second)
            {
                // ignore disables renderables
                if (renderable.gameObject->IsActive() == false &&
                    //                    renderable.m_MaterialComponent->IsActive()
                    //                    == true &&
                    renderable.shape->IsActive() == true)
                    continue;

                // apply material
                //                renderable.m_MaterialComponent->Apply();

                // Set model transform uniform
                //                renderable.m_MaterialComponent->SetModelTransform(
                //                    renderable.m_TransformComponent->AsFloat());

                // draw shape
                if (renderable.shape->IsIndexed() == true)
                {
                    // draw with indices
                    glDrawElements(
                        GL_LINES,
                        renderable.shape->GetIndexCount(),
                        VERTEX_INDEX_DATA_TYPE,
                        BUFFER_OFFSET(renderable.shape->GetIndexDataIndex()));
                }
                else
                {
                    // draw without indices
                    glDrawArrays(
                        GL_LINES, 0, renderable.shape->GetTriangleCount());
                }
            }

            // Check for errors
            //            glGetLastError();
        }
    }

    void SetShapeBufferIndex(ShapeComponent* shapeComponent)
    {
        assert(shapeComponent->GetShapeID() != IShape::Type::INVALID_SHAPE &&
               "RenderSystem got Entity with invalid shape.");

        if (this->bufferedShapes[shapeComponent->GetShapeID()] != nullptr)
        {
            // set indices
            shapeComponent->SetShapeBufferIndex(
                *this->bufferedShapes[shapeComponent->GetShapeID()]);
            return;
        }

        // Shape is not buffered yet.
        ShapeBufferIndex* bufferIndex = new ShapeBufferIndex;
        this->bufferedShapes[shapeComponent->GetShapeID()] = bufferIndex;

        // bind global vertex buffer
        this->vertexBuffer->Bind();

        // buffer vertex position data
        {
            assert(shapeComponent->GetPosition() != nullptr &&
                   "Invalid shape. Shape has no vertex position data!");
            bufferIndex->positionDataIndex =
                this->vertexBuffer->BufferVertexData(
                    shapeComponent->GetPosition(),
                    VERTEX_POSITION_DATA_ELEMENT_SIZE *
                        shapeComponent->GetVertexCount());
        }

        // buffer vertex index data
        if (shapeComponent->GetIndexCount() > 0 &&
            shapeComponent->GetIndex() != nullptr)
        {
            this->indexBuffer->Bind();
            {
                bufferIndex->indexDataIndex =
                    this->indexBuffer->BufferIndexData(
                        shapeComponent->GetIndex(),
                        VERTEX_INDEX_DATA_ELEMENT_SIZE *
                            shapeComponent->GetIndexCount());
            }
            this->indexBuffer->Unbind();
        }

        // buffer vertex normal data
        if (shapeComponent->GetNormal() != nullptr)
        {
            bufferIndex->normalDataIndex = this->vertexBuffer->BufferVertexData(
                shapeComponent->GetNormal(),
                VERTEX_NORMAL_DATA_ELEMENT_SIZE *
                    shapeComponent->GetVertexCount());
        }

        // buffer vertex uv data
        if (shapeComponent->GetTexCoord() != nullptr)
        {
            bufferIndex->texCoordDataIndex =
                this->vertexBuffer->BufferVertexData(
                    shapeComponent->GetTexCoord(),
                    VERTEX_TEXCOORD_DATA_ELEMENT_SIZE *
                        shapeComponent->GetVertexCount());
        }

        // buffer vertex color data
        if (shapeComponent->GetColor() != nullptr)
        {
            bufferIndex->colorDataIndex = this->vertexBuffer->BufferVertexData(
                shapeComponent->GetColor(),
                VERTEX_COLOR_DATA_ELEMENT_SIZE *
                    shapeComponent->GetVertexCount());
        }

        // unbind global vertex buffer
        this->vertexBuffer->Unbind();

        // set indices
        shapeComponent->SetShapeBufferIndex(*bufferIndex);
    }

    void RegisterRenderable(ecs::IEntity* entity, TransformComponent* position)
    {
        /*
        const RenderableGroupID RGID = CreateRenderableGroupID(material, shape);

        // check if there is already a group for this renderable
        for (auto it : this->m_RenderableGroups)
        {
            if (it.first.m_GroupID == RGID)
            {
                // place renderable in this group
                this->m_RenderableGroups[RGID].push_back(
                    Renderable(entity, transform, material, shape));
                return;
            }
        }

        // There is no group for this renderable yet, create a new one
        RenderableGroup renderableGroup(RGID, *material);
        {
            // Configure render state
            renderableGroup.m_VertexArray->Bind();
            {
                // bind global vertex buffer
                this->m_VertexBuffer->Bind();

                // buffer vertex position data
                MaterialVertexAttributeLoc positionVertexAttribute =
                    material->GetPositionVertexAttributeLocation();
                assert(positionVertexAttribute !=
                           INVALID_MATERIAL_VERTEX_ATTRIBUTE_LOC &&
                       "Material of a renderable does not provide a position "
                       "vertex "
                       "attribute!");

                glEnableVertexAttribArray(positionVertexAttribute);
                glVertexAttribPointer(
                    positionVertexAttribute,
                    VERTEX_POSITION_DATA_ELEMENT_LEN,
                    VERTEX_POSITION_DATA_TYPE,
                    GL_FALSE,
                    0,
                    BUFFER_OFFSET(shape->GetPositionDataIndex()));

                // buffer vertex index data
                if (shape->GetIndexCount() > 0 && shape->GetIndex() != nullptr)
                {
                    this->m_IndexBuffer->Bind();
                }

                // buffer vertex normal data
                MaterialVertexAttributeLoc normalVertexAttribute =
                    material->GetNormalVertexAttributeLocation();
                if (shape->GetNormal() != nullptr &&
                    normalVertexAttribute !=
                        INVALID_MATERIAL_VERTEX_ATTRIBUTE_LOC)
                {
                    glEnableVertexAttribArray(normalVertexAttribute);
                    glVertexAttribPointer(
                        normalVertexAttribute,
                        VERTEX_NORMAL_DATA_ELEMENT_LEN,
                        VERTEX_NORMAL_DATA_TYPE,
                        GL_FALSE,
                        0,
                        BUFFER_OFFSET(shape->GetNormalDataIndex()));
                }

                // buffer vertex uv data
                MaterialVertexAttributeLoc texCoordVertexAttribute =
                    material->GetTexCoordVertexAttributeLocation();
                if (shape->GetTexCoord() != nullptr &&
                    texCoordVertexAttribute !=
                        INVALID_MATERIAL_VERTEX_ATTRIBUTE_LOC)
                {
                    glEnableVertexAttribArray(texCoordVertexAttribute);
                    glVertexAttribPointer(
                        texCoordVertexAttribute,
                        VERTEX_TEXCOORD_DATA_ELEMENT_LEN,
                        VERTEX_TEXCOORD_DATA_TYPE,
                        GL_FALSE,
                        0,
                        BUFFER_OFFSET(shape->GetTexCoordDataIndex()));
                }

                // buffer vertex color data
                MaterialVertexAttributeLoc colorVertexAttribute =
                    material->GetColorVertexAttributeLocation();
                if (shape->GetColor() != nullptr &&
                    colorVertexAttribute !=
                        INVALID_MATERIAL_VERTEX_ATTRIBUTE_LOC)
                {
                    glEnableVertexAttribArray(colorVertexAttribute);
                    glVertexAttribPointer(
                        colorVertexAttribute,
                        VERTEX_COLOR_DATA_ELEMENT_LEN,
                        VERTEX_COLOR_DATA_TYPE,
                        GL_FALSE,
                        0,
                        BUFFER_OFFSET(shape->GetColorDataIndex()));
                }
            }
            renderableGroup.m_VertexArray->Unbind();

            this->m_VertexBuffer->Unbind();
            this->m_IndexBuffer->Unbind();
        }
        this->m_RenderableGroups[renderableGroup].push_back(
            Renderable(entity, transform, material, shape));
        */
    }
    void UnregisterRenderable(GameObjectId gameObjectId)
    {
        for (auto& RG : this->renderableGroups)
        {
            for (RenderableList::iterator it = RG.second.begin();
                 it != RG.second.end();
                 ++it)
            {
                if (it->gameObject->GetEntityID() == gameObjectId)
                {
                    RG.second.erase(it);
                    return;
                }
            }
        }
    }

private:
    VertexBuffer* vertexBuffer;
    IndexBuffer*  indexBuffer;

    BufferedShapes bufferedShapes;

    RenderableGroups renderableGroups;
};
