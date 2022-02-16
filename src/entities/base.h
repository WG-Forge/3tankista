#pragma once

#include "components/position_component.h"
#include "game/game_object.h"

class Base : public GameObject<Base>
{
public:
    Base(const ecs::EntityId&   entityId,
         ecs::ComponentManager* componentManager);
    ~Base() override = default;

private:
    PositionComponent* position;
};
