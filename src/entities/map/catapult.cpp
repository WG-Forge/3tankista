#include "catapult.h"

Catapult::Catapult(const ecs::EntityId&   entityId,
                   ecs::ComponentManager* componentManager,
                   const std::size_t      size,
                   const Vector3i&        position,
                   const Color&           color)
    : GameObject<Catapult>(entityId, componentManager)
{
    Shape shape = ShapeGenerator::CreateShape<HexShape>(size);

    this->catapultId = AddComponent<CatapultIdComponent>();
    this->AddComponent<ShapeComponent>(shape);
    this->transform = this->AddComponent<TransformComponent>(position);
    this->material = this->AddComponent<MaterialComponent>(MaterialGenerator::CreateMaterial<DefaultMaterial>(), color);
}