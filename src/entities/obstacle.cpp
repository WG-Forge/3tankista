#include "obstacle.h"

Obstacle::Obstacle(GameObjectId spawnId)
{
    this->position = AddComponent<PositionComponent>(Vector3i{ 0, 0, 0 });
}
