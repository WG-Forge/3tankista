#pragma once

#include "components/position_component.h"
#include "game/game_object.h"
#include <memory>

class Obstacle : public GameObject<Obstacle>
{
public:
    Obstacle(const ecs::EntityId&   entityId,
             ecs::ComponentManager* componentManager);
    ~Obstacle() override = default;

private:
    PositionComponent* position;
};
