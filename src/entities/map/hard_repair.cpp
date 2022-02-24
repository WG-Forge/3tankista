#include "hard_repair.h"

HardRepair::HardRepair(const ecs::EntityId& entityId, ecs::ComponentManager* componentManager, const Vector3i& position)
    : GameObject<HardRepair>(entityId, componentManager)
{
    Shape shape = ShapeGenerator::CreateShape<HexShape>(1);
    this->AddComponent<ShapeComponent>(shape);
    this->transform = this->AddComponent<TransformComponent>(position);
    this->material  = this->AddComponent<MaterialComponent>(MaterialGenerator::CreateMaterial<DefaultMaterial>(),
                                                           Color(0.55f, 0.14f, 0.56f, 1.0f));
}