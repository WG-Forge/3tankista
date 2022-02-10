#include "obstacle.h"

Obstacle::Obstacle()
{
    this->position = AddComponent<PositionComponent>(Vector3i{ 0, 0, 0 });
}
