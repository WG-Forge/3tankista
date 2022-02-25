#include "light_repair.h"

#include "render/shapes/quad_shape.h"

LightRepair::LightRepair(const ecs::EntityId&   entityId,
                         ecs::ComponentManager* componentManager,
                         const Vector3i&        position)
    : GameObject<LightRepair>(entityId, componentManager)
{
    Shape shape = ShapeGenerator::CreateShape<QuadShape>();

    this->AddComponent<ShapeComponent>(shape);
    this->transform = this->AddComponent<TransformComponent>(position);
    this->transform->GetTransform().SetScale(Vector3f{ 2.2f, 1.4f, 1.0f });
    this->material         = this->AddComponent<MaterialComponent>(MaterialGenerator::CreateMaterial<DefaultMaterial>(),
                                                           Color(1.0f, 1.0f, 1.0f, 1.0f));
    this->textureComponent = this->AddComponent<TextureComponent>(LIGHT_REPAIR_TEXTURE_NAME);
}
