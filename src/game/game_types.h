#pragma once

#include "ecs.h"

enum GameState
{
    NOT_INITIALIZED = 0,
    INITIALIZED,
    RESTARTED,
    STARTED,
    RUNNING,
    GAMEFINISHED,
    TERMINATED,
    MAX_GAMESTATES
}; // enum GameState

using GameObjectId = ecs::EntityId;

static const GameObjectId INVALID_GAMEOBJECT_ID{ ecs::INVALID_ENTITY_ID };
