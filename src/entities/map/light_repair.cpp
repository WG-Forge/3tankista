#include "light_repair.h"

LightRepair::LightRepair(const ecs::EntityId&   entityId,
                         ecs::ComponentManager* componentManager,
                         const std::size_t      size,
                         const Vector3i&        position,
                         const Color&           color)
    : GameObject<LightRepair>(entityId, componentManager)
{
    Shape shape = ShapeGenerator::CreateShape<HexShape>(size);

    this->lightRepairId = AddComponent<LightRepairIdComponent>();
    this->AddComponent<ShapeComponent>(shape);
    this->transform = this->AddComponent<TransformComponent>(position);
    this->material = this->AddComponent<MaterialComponent>(MaterialGenerator::CreateMaterial<DefaultMaterial>(), color);
}