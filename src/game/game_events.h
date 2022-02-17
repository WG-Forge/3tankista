#pragma once

#include "ecs.h"
#include "game/models/models.h"
#include <utility>

// ServerSystem events

struct SendActionEvent : public ecs::event::Event<SendActionEvent>
{
    ServerSystem::Action action;
    nlohmann::json       json;

    SendActionEvent(const ServerSystem::Action action,
                    const nlohmann::json&      json)
        : action(action)
        , json(json)
    {
    }
};

struct ReceiveActionEvent : public ecs::event::Event<ReceiveActionEvent>
{
    ServerSystem::Action action;
    nlohmann::json       sentJson;
    ServerSystem::Result result;
    nlohmann::json       json;

    ReceiveActionEvent(const ServerSystem::Action action,
                       const nlohmann::json&      sentJson,
                       const ServerSystem::Result result,
                       const nlohmann::json&      json)
        : action(action)
        , sentJson(sentJson)
        , result(result)
        , json(json)
    {
    }
};

// AdapterSystem events

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

struct LogoutRequestEvent : public ecs::event::Event<LogoutRequestEvent>
{
};

// No logout response

struct MapRequestEvent : public ecs::event::Event<MapRequestEvent>
{
    // TODO: Add code (MapRequestEvent)
};

struct MapResponseEvent : public ecs::event::Event<MapResponseEvent>
{
    // TODO: Add code (MapResponseEvent)
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

struct TurnRequestEvent : public ecs::event::Event<TurnRequestEvent>
{
};

// No turn response

struct ChatRequestEvent : public ecs::event::Event<ChatRequestEvent>
{
    // TODO: add code (ChatRequestEvent)
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

struct MoveRequestEvent : public ecs::event::Event<MoveRequestEvent>
{
    // TODO: add code (MoveResponseEvent)
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

struct ShootRequestEvent : public ecs::event::Event<ShootRequestEvent>
{
    // TODO: add code MoveRequestEvent
};

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

// Other Inner Events

struct GameLoginEvent : public ecs::event::Event<GameLoginEvent>
{
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

struct PlayEvent : public ecs::event::Event<PlayEvent>
{
};