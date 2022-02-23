#pragma once

#include "game/game_object.h"

class Text : public GameObject<Text>
{
public:
    Text(const ecs::EntityId& entityId, ecs::ComponentManager* componentManager);
};
