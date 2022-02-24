#include "light_repair.h"

LightRepair::LightRepair(const ecs::EntityId&   entityId,
                         ecs::ComponentManager* componentManager,
                         const Vector3i&        position)
    : GameObject<LightRepair>(entityId, componentManager)
{
    Shape shape = ShapeGenerator::CreateShape<HexShape>(1);

    this->AddComponent<ShapeComponent>(shape);
    this->transform = this->AddComponent<TransformComponent>(position);
    this->material  = this->AddComponent<MaterialComponent>(MaterialGenerator::CreateMaterial<DefaultMaterial>(),
                                                           Color(0.55f, 0.84f, 0.96f, 1.0f));
}