#pragma once

#include "game/game_object.h"
#include "components/position_component.h"

class Base : GameObject<Base>
{
public:
    Base(const ecs::EntityId &entityId, ecs::ComponentManager *componentManager);
    ~Base() override = default;

private:
    PositionComponent* position;
};
