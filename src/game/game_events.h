#pragma once

#include "ecs.h"
#include "enums/action.h"
#include "enums/result.h"
#include "nlohmann/json.hpp"
#include <utility>

// ServerSystem events

struct SendActionEvent : public ecs::event::Event<SendActionEvent>
{
    Action      action;
    std::string data;

    SendActionEvent(const Action action, std::string data)
        : action(action)
        , data(std::move(data))
    {
    }
};

struct ReceiveActionEvent : public ecs::event::Event<ReceiveActionEvent>
{
    Action      action;
    std::string sentData;
    Result      result;
    std::string data;

    ReceiveActionEvent(const Action action, std::string sentData, const Result result, std::string data)
        : action(action)
        , sentData(std::move(sentData))
        , result(result)
        , data(std::move(data))
    {
    }
};

#include "game/models/models.h"
// AdapterSystem events

struct LoginRequestEvent : public ecs::event::Event<LoginRequestEvent>
{
    LoginRequestModel credentials;

    explicit LoginRequestEvent(LoginRequestModel credentials)
        : credentials(std::move(credentials))
    {
    }
};

struct LoginResponseEvent : public ecs::event::Event<LoginResponseEvent>
{
    LoginResponseModel playerData;

    explicit LoginResponseEvent(LoginResponseModel playerData)
        : playerData(std::move(playerData))
    {
    }
};

struct LogoutRequestEvent : public ecs::event::Event<LogoutRequestEvent>
{
};

// No logout response

struct MapRequestEvent : public ecs::event::Event<MapRequestEvent>
{
};

struct MapResponseEvent : public ecs::event::Event<MapResponseEvent>
{
    MapModel mapModel;

    explicit MapResponseEvent(MapModel mapModel)
        : mapModel(std::move(mapModel))
    {
    }
};

struct GameStateRequestEvent : public ecs::event::Event<GameStateRequestEvent>
{
};

struct GameStateResponseEvent : public ecs::event::Event<GameStateResponseEvent>
{
    GameStateModel gameState;

    explicit GameStateResponseEvent(GameStateModel model)
        : gameState(std::move(model))
    {
    }
};

struct GameActionsRequestEvent : public ecs::event::Event<GameActionsRequestEvent>
{
};

struct GameActionsResponseEvent : public ecs::event::Event<GameActionsResponseEvent>
{
    GameActionsModel gameActionsModel;

    explicit GameActionsResponseEvent(GameActionsModel model)
        : gameActionsModel(std::move(model))
    {
    }
};

struct TurnRequestEvent : public ecs::event::Event<TurnRequestEvent>
{
};

struct GameOverEvent : public ecs::event::Event<GameOverEvent>
{
    bool     isDraw;
    uint64_t winner;
    GameOverEvent(const bool isDraw, const uint64_t winner)
        : isDraw(isDraw)
        , winner(winner)
    {
    }
};

struct WorldCreateEvent : public ecs::event::Event<WorldCreateEvent>
{
};

// No turn response

struct ChatRequestEvent : public ecs::event::Event<ChatRequestEvent>
{
    ChatModel chatModel;

    explicit ChatRequestEvent(ChatModel data)
        : chatModel(std::move(chatModel))
    {
    }
};

struct ChatResponseEvent : public ecs::event::Event<ChatResponseEvent>
{
    int                    playerId;
    std::vector<ChatModel> actions;

    explicit ChatResponseEvent(const int playerId, std::vector<ChatModel> actions)
        : playerId(playerId)
        , actions(std::move(actions))
    {
    }
};

struct MoveRequestEvent : public ecs::event::Event<MoveRequestEvent>
{
    MoveModel model;

    explicit MoveRequestEvent(MoveModel model)
        : model(std::move(model))
    {
    }
};

struct MoveResponseEvent : public ecs::event::Event<MoveResponseEvent>
{
    uint64_t               playerId;
    std::vector<MoveModel> actions;

    explicit MoveResponseEvent(const uint64_t playerId, std::vector<MoveModel> actions)
        : playerId(playerId)
        , actions(std::move(actions))
    {
    }
};

struct ShootRequestEvent : public ecs::event::Event<ShootRequestEvent>
{
    ShootModel model;

    explicit ShootRequestEvent(ShootModel model)
        : model(std::move(model))
    {
    }
};

struct ShootResponseEvent : public ecs::event::Event<ShootResponseEvent>
{
    uint64_t                playerId;
    std::vector<ShootModel> actions;

    explicit ShootResponseEvent(const uint64_t playerId, std::vector<ShootModel> actions)
        : playerId(playerId)
        , actions(std::move(actions))
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
    GameObjectId killerEntityId;
    GameObjectId entityId;

    explicit TankDestroyedEvent(GameObjectId killer, GameObjectId id)
        : killerEntityId(killer)
        , entityId(id)
    {
    }
};

struct PlayEvent : public ecs::event::Event<PlayEvent>
{
};

struct UpdateCapturePointsEvent : public ecs::event::Event<UpdateCapturePointsEvent>
{
};

struct QuitGameEvent : public ecs::event::Event<QuitGameEvent>
{
};
