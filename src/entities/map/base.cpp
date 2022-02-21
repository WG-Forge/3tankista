#include "base.h"

Base::Base(const ecs::EntityId& entityId, ecs::ComponentManager* componentManager)
    : GameObject<Base>(entityId, componentManager)
{
    this->baseId   = AddComponent<BaseIdComponent>();
    this->position = AddComponent<PositionComponent>(Vector3i(0, 0, 0));
}
