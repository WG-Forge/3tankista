#include "gamestate.h"
#include "singleton.h"

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
    try
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
        std::unordered_map<int, std::vector<int>> am;
        for (const auto& [key, value] : j["attack_matrix"].items())
        {
            std::vector<int> ids(value);
            am.insert(std::make_pair(std::stoi(key), ids));
        }
        gs.SetAttackMatrix(am);
        std::unordered_map<int, WinPoints> wp;
        for (const auto& [key, value] : j["win_points"].items())
        {
            WinPoints tempwp;
            from_json(value, tempwp);
            wp.insert(std::make_pair(std::stoi(key), tempwp));
        }
        gs.SetWinPoints(wp);
        std::unordered_map<int, std::vector<AbstractTank*>> vehs;
        for (auto it = j["vehicles"].begin(); it != j["vehicles"].end(); ++it)
        {
            std::vector<AbstractTank*> atanks;
            int                        player_id;
            it.value().at("player_id").get_to<int>(player_id);
            if (vehs.find(player_id) != vehs.end())
            {
                atanks = vehs[player_id];
            }

            nlohmann::json j;
            j[it.key()] = it.value();
            atanks.push_back(j.get<AbstractTank*>());

            vehs.erase(player_id);
            vehs.insert(std::make_pair(player_id, atanks));
        }
        gs.SetVehicles(vehs);
    }
    catch (nlohmann::json::type_error& e)
    {
        std::cout << e.what() << std::endl << std::flush;
    }
    catch (nlohmann::json::out_of_range& e)
    {
        std::cout << e.what() << std::endl << std::flush;
    }
    catch (nlohmann::json::parse_error& e)
    {
        std::cout << e.what() << std::endl << std::flush;
    }
    catch (std::out_of_range& e)
    {
        std::cout << e.what() << std::endl << std::flush;
    }
    catch (std::invalid_argument& e)
    {
        std::cout << e.what() << std::endl << std::flush;
    }
}
