#pragma once

#include <utility>

#include "ecs.h"

#include "render/global.h"

#include "enums/action.h"
#include "enums/result.h"

#include "nlohmann/json.hpp"

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

struct TurnResponseEvent : public ecs::event::Event<TurnResponseEvent>
{
};

struct GameOverEvent : public ecs::event::Event<GameOverEvent>
{
    std::vector<std::pair<uint64_t, std::pair<int, int>>> winners;
    explicit GameOverEvent(std::vector<std::pair<uint64_t, std::pair<int, int>>> winners)
        : winners(std::move(winners))
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

struct NewTankCreated : public ecs::event::Event<NewTankCreated>
{
    GameObjectId tankId;

    NewTankCreated(const GameObjectId& tankId)
        : tankId(tankId)
    {
    }
};

struct HealthChanged : public ecs::event::Event<HealthChanged>
{
    uint64_t vehicleId;
    int      health;
    int      maxHealth;

    HealthChanged(const uint64_t vehicleId, const int health, const int maxHealth)
        : vehicleId{ vehicleId }
        , health{ health }
        , maxHealth{ maxHealth }
    {
    }
};

struct WindowMinimizedEvent : public ecs::event::Event<WindowMinimizedEvent>
{
};

struct WindowRestoredEvent : public ecs::event::Event<WindowRestoredEvent>
{
};

struct WindowResizedEvent : public ecs::event::Event<WindowResizedEvent>
{
    int width;
    int height;

    WindowResizedEvent(int w, int h)
        : width(w)
        , height(h)
    {
    }
};

struct WindowCloseEvent : public ecs::event::Event<WindowCloseEvent>
{
};

struct StartGameEvent : public ecs::event::Event<StartGameEvent>
{
};

struct BadRestartEvent : public ecs::event::Event<BadRestartEvent>
{
};
struct GameStateEvent : public ecs::event::Event<GameStateEvent>
{
};
