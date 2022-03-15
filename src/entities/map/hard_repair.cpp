#include "hard_repair.h"

#include "render/shapes/quad_shape.h"

HardRepair::HardRepair(const ecs::EntityId& entityId, ecs::ComponentManager* componentManager, const Vector3i& position)
    : GameObject<HardRepair>(entityId, componentManager)
{
    Shape shape = ShapeGenerator::CreateShape<QuadShape>();
    this->AddComponent<ShapeComponent>(shape);
    this->transform = this->AddComponent<TransformComponent>(position);
    this->transform->GetTransform().SetScale(Vector3f{ 2.1f, 1.4f, 1.0f });
    this->material         = this->AddComponent<MaterialComponent>(MaterialGenerator::CreateMaterial<DefaultMaterial>(),
                                                           Color(1.0f, 1.0f, 1.0f, 1.0f));
    this->textureComponent = this->AddComponent<TextureComponent>(HARD_REPAIR_TEXTURE_NAME);
}
