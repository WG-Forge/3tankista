#pragma once

#include "components/material_component.h"
#include "components/transform_component.h"

#include "game/game_object.h"

class Spawn : public GameObject<Spawn>
{
public:
    Spawn(const ecs::EntityId&   entityId,
          ecs::ComponentManager* componentManager,
          const Vector3i&        position,
          const Color&           color = Color(0.2f, 0.2f, 0.9f, 1.0f));
    ~Spawn() override = default;

private:
    TransformComponent* transform;
    MaterialComponent*  material;
};
