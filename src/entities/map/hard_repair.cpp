#include "hard_repair.h"

HardRepair::HardRepair(const ecs::EntityId&   entityId,
                       ecs::ComponentManager* componentManager,
                       const std::size_t      size,
                       const Vector3i&        position,
                       const Color&           color)
    : GameObject<HardRepair>(entityId, componentManager)
{
    Shape shape = ShapeGenerator::CreateShape<HexShape>(size);

    this->hardRepairId = AddComponent<HardRepairIdComponent>();
    this->AddComponent<ShapeComponent>(shape);
    this->transform = this->AddComponent<TransformComponent>(position);
    this->material = this->AddComponent<MaterialComponent>(MaterialGenerator::CreateMaterial<DefaultMaterial>(), color);
}