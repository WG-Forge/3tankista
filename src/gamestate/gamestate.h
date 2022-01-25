
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "../player.h"
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
private:
    int                                num_players;
    int                                num_turns;
    int                                current_turn;
    std::vector<Player>                players;
    std::vector<Player>                observers;
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
