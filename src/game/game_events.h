#pragma once

#include "ecs.h"
#include "entities/models/map_model.h"
#include "game/models/models.h"

struct GameLoginEvent : public ecs::event::Event<GameLoginEvent>
{
};


struct LoginRequestEvent : public ecs::event::Event<LoginRequestEvent>
{
    LoginRequestModel credentials;

    LoginRequestEvent(const LoginRequestModel& credentials)
        : credentials(credentials)
    {
    }
};

struct LoginResponceEvent : public ecs::event::Event<LoginResponceEvent>
{
    LoginResponceModel playerData;

    LoginResponceEvent(const LoginResponceModel& playerData)
        : playerData(playerData)
    {
    }
};

using GameObjectId     = ecs::EntityId;
using GameObjectTypeId = ecs::EntityTypeId;

struct GameObjectCreated : public ecs::event::Event<GameObjectCreated>
{
    GameObjectId     entityID;
    GameObjectTypeId entityTypeID;

    GameObjectCreated(GameObjectId id, GameObjectTypeId typeId)
        : entityID(id)
        , entityTypeID(typeId)
    {
    }
};

struct GameObjectDestroyed : public ecs::event::Event<GameObjectDestroyed>
{
    GameObjectId     entityID;
    GameObjectTypeId entityTypeID;

    GameObjectDestroyed(GameObjectId id, GameObjectTypeId typeId)
        : entityID(id)
        , entityTypeID(typeId)
    {
    }
};

struct TankDestroyedEvent : public ecs::event::Event<TankDestroyedEvent>
{
    GameObjectId entityId;

    TankDestroyedEvent(GameObjectId id)
        : entityId(id)
    {
    }
};

// TODO: from action system
struct ShootResponceEvent : public ecs::event::Event<ShootResponceEvent>
{
    std::vector<std::pair<GameObjectId, int>> entityIds;

    explicit ShootResponceEvent(
        std::vector<std::pair<GameObjectId, int>> entityIds)
        : entityIds(std::move(entityIds))
    {
    }
};

struct MapRequestEvent : public ecs::event::Event<MapRequestEvent>
{

};

struct MapResponceEvent : public ecs::event::Event<MapResponceEvent>
{
    MapModel mapModel;

    explicit MapResponceEvent(MapModel mapModel)
        : mapModel(std::move(mapModel))
    {
    }
};
