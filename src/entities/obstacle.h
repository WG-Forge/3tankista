#pragma once

#include "game/game_object.h"

#include "components/position_component.h"

class Obstacle : public GameObject<Obstacle>
{
public:
    Obstacle();
    explicit Obstacle(const Vector3i& position);
    ~Obstacle() override = default;

private:
    PositionComponent* position;
};
