
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "../player.h"
#include "loginresponcemodel.h"
#include "nlohmann/json.hpp"
#include <unordered_map>
#include <vector>

struct WinPoints
{
    int capture;
    int kill;
};

class GameState
{
public:
    GameState();

public:
    void        SetNumPlayers(const int& num_pl) { this->num_players = num_pl; }
    auto&       GetNumPlayers() { return this->num_players; }
    const auto& GetNumPlayers() const { return this->num_players; }

    void        SetNumTurns(const int& num_t) { this->num_turns = num_t; }
    auto&       GetNumTurns() { return this->num_turns; }
    const auto& GetNumTurns() const { return this->num_turns; }

    void        SetCurrentTurn(const int& cur_t) { this->current_turn = cur_t; }
    auto&       GetCurrentTurn() { return this->current_turn; }
    const auto& GetCurrentTurn() const { return this->current_turn; }

    void SetCurrentPlayerIdx(const int& cur_pl_idx)
    {
        this->current_player_idx = cur_pl_idx;
    }
    auto&       GetCurrentPlayerIdx() { return this->current_player_idx; }
    const auto& GetCurrentPlayerIdx() const { return this->current_player_idx; }

    void        SetFinished(const bool& fin) { this->finished = fin; }
    auto&       GetFinished() { return this->finished; }
    const auto& GetFinished() const { return this->finished; }

    void        SetWinner(const int& win) { this->winner = win; }
    auto&       GetWinner() { return this->num_players; }
    const auto& GetWinner() const { return this->num_players; }

    void  SetPlayers(const std::vector<Player>& pl) { this->players = pl; }
    auto& GetPlayers() { return this->players; }
    const auto& GetPlayers() const { return this->players; }

    void  SetObservers(const std::vector<int>& ob) { this->observers = ob; }
    auto& GetObservers() { return this->observers; }
    const auto& GetObservers() const { return this->observers; }

    void SetAttackMatrix(const std::unordered_map<int, int>& am)
    {
        this->attack_matrix = am;
    }
    auto&       GetAttackMatrix() { return this->attack_matrix; }
    const auto& GetAttackMatrix() const { return this->attack_matrix; }

private:
    int                                num_players;
    int                                num_turns;
    int                                current_turn;
    std::vector<Player>                players;
    std::vector<int>                   observers;
    int                                current_player_idx;
    bool                               finished;
    std::vector<AbstractTank>          vehicles;
    std::unordered_map<int, int>       attack_matrix;
    int                                winner;
    std::unordered_map<int, WinPoints> win_points;
};

void to_json(nlohmann::json& j, const GameState& gs);

void from_json(const nlohmann::json& j, GameState& gs);
#endif // GAMESTATE_H
