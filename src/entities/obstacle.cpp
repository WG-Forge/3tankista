#include "obstacle.h"

Obstacle::Obstacle(const ecs::EntityId&   entityId,
                   ecs::ComponentManager* componentManager)
    : GameObject<Obstacle>(entityId, componentManager)
{
    this->position = AddComponent<PositionComponent>(Vector3i{ 0, 0, 0 });
    this->obstacleId = AddComponent<ObstacleIdComponent>();
}