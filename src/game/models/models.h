#pragma once

#include <string>

#include "nlohmann/json.hpp"
#include "utility/matrix.hpp"
#include "utility/tank_types.h"

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

void from_json(const nlohmann::json& json,
               LoginRequestModel&    loginRequestModel);

struct LoginResponceModel
{
    uint64_t    index;
    std::string name;
    bool        isObserver;
};

void to_json(nlohmann::json&           json,
             const LoginResponceModel& loginResponceModel);

void from_json(const nlohmann::json& json,
               LoginResponceModel&   loginResponceModel);

struct PlayerModel
{
    int         idx;
    std::string name;
    bool        isObserver;
};

struct TankModel
{
    int      playerId;
    TankType vehicleType;
    int      health;
    Vector3i spawnPosition;
    Vector3i position;
    int      capturePoints;
};

struct WinPointsModel
{
    int capture;
    int kill;
};

struct GameStateModel
{
    int                                       numberPlayers;
    int                                       numberTurns;
    int                                       currentTurn;
    std::vector<PlayerModel>                  players;
    std::vector<PlayerModel>                  observers;
    int                                       currentPlayerIndex;
    bool                                      finished;
    std::unordered_map<int, TankModel>        vehicles;
    std::unordered_map<int, std::vector<int>> attackMatrix;
    int                                       winner;
    std::unordered_map<int, WinPointsModel>   winPoints;
};