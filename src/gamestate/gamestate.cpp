#include "gamestate.h"
GameState::GameState()
    : num_players()
    , num_turns()
    , current_turn()
    , players()
    , observers()
    , current_player_idx()
    , finished()
    , vehicles()
    , attack_matrix()
    , winner()
    , win_points()
{
}

void to_json(nlohmann::json& j, const GameState& gs) {}

void from_json(const nlohmann::json& j, GameState& gs)
{
    j.at("num_players").get_to<int>(gs.GetNumPlayers());
    j.at("num_turns").get_to<int>(gs.GetNumTurns());
    j.at("current_turn").get_to<int>(gs.GetCurrentTurn());
    j.at("num_players").get_to<int>(gs.GetNumPlayers());
    j.at("current_player_idx").get_to<int>(gs.GetCurrentPlayerIdx());
    j.at("finished").get_to<bool>(gs.GetFinished());
    if (j.at("winner").empty())
    {
        gs.SetWinner(0);
    }
    else
    {
        j.at("winner").get_to<int>(gs.GetWinner());
    }
    j.at("players").get_to<std::vector<Player>>(gs.GetPlayers());
    j.at("observers").get_to<std::vector<int>>(gs.GetObservers());
    std::unordered_map<int, int> am;
    for (const auto& [key, value] : j["attack_matrix"].items())
    {
        std::vector<int> ids(value);
        
    }
}
