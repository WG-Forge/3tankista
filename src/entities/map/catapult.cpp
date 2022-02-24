#include "catapult.h"

Catapult::Catapult(const ecs::EntityId& entityId, ecs::ComponentManager* componentManager, const Vector3i& position)
    : GameObject<Catapult>(entityId, componentManager)
{
    Shape shape = ShapeGenerator::CreateShape<HexShape>(1);

    this->AddComponent<ShapeComponent>(shape);
    this->transform = this->AddComponent<TransformComponent>(position);
    this->material  = this->AddComponent<MaterialComponent>(MaterialGenerator::CreateMaterial<DefaultMaterial>(),
                                                           Color(0.95f, 0.84f, 0.56f, 1.0f));
    this->usage     = this->AddComponent<UsageComponent>(0);
}