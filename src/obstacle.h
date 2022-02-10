#pragma once

#include "game_object.h"

#include "position_component.h"

class Obstacle : public GameObject<Obstacle>
{
public:
    Obstacle();
    explicit Obstacle(const Vector3i& position);
    ~Obstacle() override = default;

private:
    PositionComponent* position;
};
