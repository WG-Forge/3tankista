#pragma once

#include "game/game_object.h"
#include <memory>
#include "components/position_component.h"

class Obstacle : public GameObject<Obstacle>
{
public:
    explicit Obstacle(GameObjectId spawnId);
    ~Obstacle() override = default;

private:
    PositionComponent* position;
};
