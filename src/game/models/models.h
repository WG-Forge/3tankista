#pragma once

#include <string>
#include <variant>

#include "ecs.h"
#include "enums/action.h"
#include "enums/tank_types.h"
#include "nlohmann/json.hpp"
#include "utility/matrix.hpp"

using GameObjectId     = ecs::EntityId;
using GameObjectTypeId = ecs::EntityTypeId;

struct LoginRequestModel
{
    std::string name;
    std::string password;
    std::string game;
    uint64_t    numberTurns;
    uint64_t    numberPlayers;
    bool        isObserver;
};

void to_json(nlohmann::json& json, const LoginRequestModel& loginRequestModel);

void from_json(const nlohmann::json& json, LoginRequestModel& loginRequestModel);

struct LoginResponseModel
{
    uint64_t    index;
    std::string name;
    bool        isObserver;
};

void to_json(nlohmann::json& json, const LoginResponseModel& loginResponseModel);

void from_json(const nlohmann::json& json, LoginResponseModel& loginResponseModel);

struct PlayerModel
{
    int         idx;
    std::string name;
    bool        isObserver;
};

void to_json(nlohmann::json& json, const PlayerModel& playerModel);

void from_json(const nlohmann::json& json, PlayerModel& playerModel);

struct TankModel
{
    int      playerId;
    TankType vehicleType;
    int      health;
    Vector3i spawnPosition;
    Vector3i position;
    int      capturePoints;
};

void to_json(nlohmann::json& json, const TankModel& tankModel);

void from_json(const nlohmann::json& json, TankModel& tankModel);

struct WinPointsModel
{
    int capture;
    int kill;
};

void to_json(nlohmann::json& json, const WinPointsModel& winPointsModel);

void from_json(const nlohmann::json& json, WinPointsModel& winPointsModel);

struct GameStateModel
{
    int                                       numberPlayers;
    int                                       numberTurns;
    int                                       currentTurn;
    std::vector<PlayerModel>                  players;
    std::vector<PlayerModel>                  observers;
    int                                       currentPlayerIndex;
    bool                                      finished;
    std::vector<std::pair<int, TankModel>>    vehicles;
    std::unordered_map<int, std::vector<int>> attackMatrix;
    int                                       winner;
    std::unordered_map<int, WinPointsModel>   winPoints;
};

void to_json(nlohmann::json& json, const GameStateModel& gameStateModel);

void from_json(const nlohmann::json& json, GameStateModel& gameStateModel);

struct ShootModel
{
    uint64_t vehicleId;
    Vector3i target;
};

void to_json(nlohmann::json& json, const ShootModel& shootModel);

void from_json(const nlohmann::json& json, ShootModel& shootModel);

struct MoveModel
{
    uint64_t vehicleId;
    Vector3i target;
};

void to_json(nlohmann::json& json, const MoveModel& moveModel);

void from_json(const nlohmann::json& json, MoveModel& moveModel);

struct ChatModel
{
    std::string message;
};

void to_json(nlohmann::json& json, const ChatModel& chatModel);

void from_json(const nlohmann::json& json, ChatModel& chatModel);

struct ActionModel
{
    uint64_t                                       playerIndex;
    Action                                         actionType;
    std::variant<ShootModel, MoveModel, ChatModel> data;
};

void to_json(nlohmann::json& json, const ActionModel& actionModel);

void from_json(const nlohmann::json& json, ActionModel& actionModel);

struct GameActionsModel
{
    std::vector<ActionModel> actions;
};

void to_json(nlohmann::json& json, const GameActionsModel& gameActionsModel);

void from_json(const nlohmann::json& json, GameActionsModel& gameActionsModel);

struct SpawnPointsModel
{
    std::vector<std::pair<TankType, std::vector<Vector3i>>> spawnPoints;
};

void to_json(nlohmann::json& json, const SpawnPointsModel& spawnPointsModel);

void from_json(const nlohmann::json& json, SpawnPointsModel& spawnPointsModel);

struct MapModel
{
    std::vector<SpawnPointsModel> mapSpawnPoints;
    std::vector<Vector3i>         obstacle;
    std::vector<Vector3i>         base;
    int                           size;
    std::string                   name;
};

void to_json(nlohmann::json& json, const MapModel& mapModel);

void from_json(const nlohmann::json& json, MapModel& mapModel);
