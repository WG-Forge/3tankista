
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "enumparser.h"
#include "loginresponcemodel.h"
#include "matrix.hpp"
#include "mediumtank.h"
#include "nlohmann/json.hpp"
#include "player.h"
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
    void SetNumPlayers(const int& numberPlayers)
    {
        this->numberPlayers = numberPlayers;
    }
    auto       GetNumPlayers() { return this->numberPlayers; }
    const auto GetNumPlayers() const { return this->numberPlayers; }

    void SetNumTurns(const int& numberTurns)
    {
        this->numberTurns = numberTurns;
    }
    auto       GetNumTurns() { return this->numberTurns; }
    const auto GetNumTurns() const { return this->numberTurns; }

    void SetCurrentTurn(const int& currentTurn)
    {
        this->currentTurn = currentTurn;
    }
    auto       GetCurrentTurn() { return this->currentTurn; }
    const auto GetCurrentTurn() const { return this->currentTurn; }

    void SetCurrentPlayerIdx(const int& currentPlayerIndex)
    {
        this->currentPlayerIndex = currentPlayerIndex;
    }
    auto       GetCurrentPlayerIdx() { return this->currentPlayerIndex; }
    const auto GetCurrentPlayerIdx() const { return this->currentPlayerIndex; }

    void       SetFinished(const bool& finished) { this->finished = finished; }
    auto       GetFinished() { return this->finished; }
    const auto GetFinished() const { return this->finished; }

    void       SetWinner(const int& winner) { this->winner = winner; }
    auto       GetWinner() { return this->winner; }
    const auto GetWinner() const { return this->winner; }

    void SetPlayers(const std::vector<Player>& players)
    {
        this->players = players;
    }
    auto&       GetPlayers() { return this->players; }
    const auto& GetPlayers() const { return this->players; }

    void SetObservers(const std::vector<Player>& observers)
    {
        this->observers = observers;
    }
    auto&       GetObservers() { return this->observers; }
    const auto& GetObservers() const { return this->observers; }

    void SetAttackMatrix(
        const std::unordered_map<int, std::vector<int>>& attackMatrix)
    {
        this->attackMatrix = attackMatrix;
    }
    auto&       GetAttackMatrix() { return this->attackMatrix; }
    const auto& GetAttackMatrix() const { return this->attackMatrix; }

    void SetWinPoints(const std::unordered_map<int, WinPoints>& winPoints)
    {
        this->winPoints = winPoints;
    }
    auto&       GetWinPoints() { return this->winPoints; }
    const auto& GetWinPoints() const { return this->winPoints; }

    void SetVehicles(const MapPlayerIDAndTank& vehicles)
    {
        this->vehicles = vehicles;
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

#endif // GAMESTATE_H
