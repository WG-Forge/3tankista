#pragma once

#include "components/base_id_component.h"
#include "components/material_component.h"
#include "components/transform_component.h"
#include "game/game_object.h"

class Base : public GameObject<Base>
{
public:
    Base(const ecs::EntityId&   entityId,
         ecs::ComponentManager* componentManager,
         const std::size_t      size,
         const Vector3i&        position,
         const Color&           color);
    ~Base() override = default;

private:
    BaseIdComponent*    baseId;
    TransformComponent* transform;
    MaterialComponent*  material;
};