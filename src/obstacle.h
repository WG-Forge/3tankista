#pragma once

#include "game_object.h"

#include "position_component.h"

class Obstacle : public GameObject<Obstacle>
{
public:
    Obstacle();
    Obstacle(const Vector3i& position);
    virtual ~Obstacle() = default;

private:
    PositionComponent* position;
};
