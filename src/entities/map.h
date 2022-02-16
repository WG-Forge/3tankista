#pragma once

#include "game/game_object.h"

#include "components/material_component.h"
#include "components/position_component.h"

#include "ecs.h"

class Map : public GameObject<Map>
{

public:
    Map(const ecs::EntityId& entityId, ecs::ComponentManager* componentManager);
    virtual ~Map() = default;

private:
    PositionComponent* position;
    MaterialComponent* material;
};
