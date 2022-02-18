#pragma once

#include "game/game_events.h"
#include "game/game_types.h"

#include "render_utility/renderable.h"

#include "ecs.h"

#include "glad.h"

#include "GLFW/glfw3.h"

// TODO: 1) draw line using render
//       2) draw triangle from lines
//       3) draw hex from lines
//       4) draw hex field
class RenderSystem : public ecs::System<RenderSystem>,
                     public ecs::event::IEventListener
{
    static constexpr size_t GLOBAL_VERTEX_BUFFER_SIZE{ 8388608 /* 8 MB */ };
    static constexpr size_t GLOBAL_INDEX_BUFFER_SIZE{ 8388608 /* 8 MB */ };

    static inline const RenderableGroupID CreateRenderableGroupID(
        MaterialComponent* material, ShapeComponent* shape)
    {
        return ((material->GetMaterialID() << 16) | shape->GetShapeID());
    }

    using BufferedShapes = std::vector<ShapeBufferIndex*>;

public:
    RenderSystem(GLFWwindow* window);
    virtual ~RenderSystem();

    virtual void PreUpdate(float dt) override;
    virtual void Update(float dt) override;
    virtual void PostUpdate(float dt) override;

private:
    void InitializeOpenGL();
    void TerminateOpenGL();

    void RegisterEventCallbacks();
    void UnregisterEventCallbacks();

    void SetShapeBufferIndex(ShapeComponent* shapeComponent);

    void RegisterRenderable(ecs::IEntity*       entity,
                            TransformComponent* transform,
                            MaterialComponent*  material,
                            ShapeComponent*     shape);
    void UnregisterRenderable(GameObjectId gameObjectId);

    void OnWindowResized(const WindowResizedEvent* event);
    void OnWindowMinimized(const WindowMinimizedEvent* event);
    void OnWindowRestored(const WindowRestoredEvent* event);

    void OnGameObjectCreated(const GameObjectCreated* event);
    void OnGameObjectDestroyed(const GameObjectDestroyed* event);

private:
    GLFWwindow* window;

    VertexBuffer* vertexBuffer;
    IndexBuffer*  indexBuffer;

    // Keeps track of already buffered shapes
    BufferedShapes bufferedShapes;

    // A set of all currently registered randerable entities
    RenderableGroups renderableGroups;
};
