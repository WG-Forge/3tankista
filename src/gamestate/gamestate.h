
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <vector>
#include "../player.h"
#include "nlohmann/json.hpp"
class GameState
{
public:
    GameState();

public:

private:
    int                  num_players;
    int                  num_turns;
    int                  current_turn;
    std::vector<Player> players;
};

void to_json(nlohmann::json& j, const GameState& gs);

void from_json(const nlohmann::json& j, GameState& gs);
#endif // GAMESTATE_H
