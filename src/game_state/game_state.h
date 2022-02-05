#pragma once

#include "client/player.h"
#include "nlohmann/json.hpp"
#include "server/models/login_responce_model.h"
#include "tanks/medium_tank.h"
#include "utility/enum_parser.h"
#include "utility/matrix.hpp"
#include <sstream>
#include <unordered_map>
#include <vector>

struct WinPoints
{
    int kill;
    int capture;
};

void to_json(nlohmann::json& json, const WinPoints& winPoints);

void from_json(const nlohmann::json& json, WinPoints& winPoints);

class GameState
{
public:
    using MapPlayerIDAndTank =
        std::unordered_map<int, std::vector<std::shared_ptr<AbstractTank>>>;

public:
    GameState() = default;

public:
    void SetNumPlayers(const int numberPlayers)
    {
        this->numberPlayers = numberPlayers;
    }
    auto GetNumPlayers() const { return this->numberPlayers; }

    void SetNumTurns(const int numberTurns) { this->numberTurns = numberTurns; }
    auto GetNumTurns() const { return this->numberTurns; }

    void SetCurrentTurn(const int currentTurn)
    {
        this->currentTurn = currentTurn;
    }
    auto GetCurrentTurn() const { return this->currentTurn; }

    void SetCurrentPlayerIdx(const int currentPlayerIndex)
    {
        this->currentPlayerIndex = currentPlayerIndex;
    }
    auto GetCurrentPlayerIdx() const { return this->currentPlayerIndex; }

    void SetFinished(const bool finished) { this->finished = finished; }
    auto GetFinished() const { return this->finished; }

    void SetWinner(const int winner) { this->winner = winner; }
    auto GetWinner() const { return this->winner; }

    void SetPlayers(std::vector<Player>& players)
    {
        this->players = std::move(players);
    }
    auto&       GetPlayers() { return this->players; }
    const auto& GetPlayers() const { return this->players; }

    void SetObservers(std::vector<Player>& observers)
    {
        this->observers = std::move(observers);
    }
    auto&       GetObservers() { return this->observers; }
    const auto& GetObservers() const { return this->observers; }

    void SetAttackMatrix(
        std::unordered_map<int, std::vector<int>>& attackMatrix)
    {
        this->attackMatrix = std::move(attackMatrix);
    }
    auto&       GetAttackMatrix() { return this->attackMatrix; }
    const auto& GetAttackMatrix() const { return this->attackMatrix; }

    void SetWinPoints(std::unordered_map<int, WinPoints>& winPoints)
    {
        this->winPoints = std::move(winPoints);
    }
    auto&       GetWinPoints() { return this->winPoints; }
    const auto& GetWinPoints() const { return this->winPoints; }

    void SetVehicles(MapPlayerIDAndTank& vehicles)
    {
        this->vehicles = std::move(vehicles);
    }
    auto&       GetVehicles() { return this->vehicles; }
    const auto& GetVehicles() const { return this->vehicles; }

private:
    int                                       numberPlayers;
    int                                       numberTurns;
    int                                       currentTurn;
    std::vector<Player>                       players;
    std::vector<Player>                       observers;
    int                                       currentPlayerIndex;
    bool                                      finished;
    MapPlayerIDAndTank                        vehicles;
    std::unordered_map<int, std::vector<int>> attackMatrix;
    int                                       winner;
    std::unordered_map<int, WinPoints>        winPoints;
};

void to_json(nlohmann::json& json, const GameState& gameState);

void from_json(const nlohmann::json& json, GameState& gameState);
