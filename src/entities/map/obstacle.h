#pragma once

#include "components/obstacle_id_component.h"
#include "components/material_component.h"
#include "components/transform_component.h"
#include "game/game_object.h"

#include <memory>

class Obstacle : public GameObject<Obstacle>
{
public:
    Obstacle(const ecs::EntityId&   entityId,
             ecs::ComponentManager* componentManager,
             const Vector3i&        position);
    ~Obstacle() override = default;

private:
	ObstacleIdComponent* obstacleId;
    TransformComponent* transform;
    MaterialComponent*  material;
};
