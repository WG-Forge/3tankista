#pragma once

#include "ecs.h"
#include "game/models/models.h"
#include <utility>

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

struct LoginResponseEvent : public ecs::event::Event<LoginResponseEvent>
{
    LoginResponseModel playerData;

    LoginResponseEvent(const LoginResponseModel& playerData)
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
struct ShootResponseEvent : public ecs::event::Event<ShootResponseEvent>
{
    int                     playerId;
    std::vector<ShootModel> actions;

    explicit ShootResponseEvent(const int                      playerId,
                                const std::vector<ShootModel>& actions)
        : playerId(playerId)
        , actions(actions)
    {
    }
};

struct ChatResponseEvent : public ecs::event::Event<ChatResponseEvent>
{
    int                    playerId;
    std::vector<ChatModel> actions;

    explicit ChatResponseEvent(const int                     playerId,
                               const std::vector<ChatModel>& actions)
        : playerId(playerId)
        , actions(actions)
    {
    }
};

struct MoveResponseEvent : public ecs::event::Event<MoveResponseEvent>
{
    int                    playerId;
    std::vector<MoveModel> actions;

    explicit MoveResponseEvent(const int                     playerId,
                               const std::vector<MoveModel>& actions)
        : playerId(playerId)
        , actions(actions)
    {
    }
};

struct GameStateRequestEvent : public ecs::event::Event<GameStateRequestEvent>
{
    // TODO: Add code (GameStateRequestEvent)
};

struct GameStateResponseEvent : public ecs::event::Event<GameStateResponseEvent>
{
    GameStateModel gameState;

    explicit GameStateResponseEvent(const GameStateModel& model)
        : gameState(model)
    {
    }
};

struct GameActionsRequestEvent
    : public ecs::event::Event<GameActionsRequestEvent>
{
    // TODO: Add code (GameActionsRequestEvent)
};

struct GameActionsResponseEvent
    : public ecs::event::Event<GameActionsResponseEvent>
{
    GameActionsModel gameActionsModel;

    explicit GameActionsResponseEvent(const GameActionsModel& model)
        : gameActionsModel(model)
    {
    }
};