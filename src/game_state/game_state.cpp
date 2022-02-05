#include "game_state.h"
#include "utility/singleton.h"

void to_json(nlohmann::json& json, const GameState& gameState)
{
    json = nlohmann::json{ "" };
}

void from_json(const nlohmann::json& json, GameState& gameState)
{
    try
    {
        gameState.SetNumPlayers(json.at("num_players"));
        gameState.SetNumTurns(json.at("num_turns"));
        gameState.SetCurrentTurn(json.at("current_turn"));
        if (json.at("current_player_idx").empty())
        {
            gameState.SetCurrentPlayerIdx(0);
        }
        else
        {
            gameState.SetCurrentPlayerIdx(json.at("current_player_idx"));
        }
        gameState.SetFinished(json.at("finished"));
        if (json.at("winner").empty())
        {
            gameState.SetWinner(0);
        }
        else
        {
            gameState.SetWinner(json.at("winner"));
        }
        json.at("players").get_to<std::vector<Player>>(gameState.GetPlayers());
        json.at("observers")
            .get_to<std::vector<Player>>(gameState.GetObservers());
        std::unordered_map<int, std::vector<int>> attackMatrix;
        for (const auto& [key, value] : json["attack_matrix"].items())
        {
            std::vector<int> ids(value);
            attackMatrix.insert(std::make_pair(std::stoi(key), ids));
        }
        gameState.SetAttackMatrix(attackMatrix);
        std::unordered_map<int, WinPoints> winPoints;
        for (const auto& [key, value] : json["win_points"].items())
        {
            WinPoints tempwp{};
            from_json(value, tempwp);
            winPoints.insert(std::make_pair(std::stoi(key), tempwp));
        }
        gameState.SetWinPoints(winPoints);
        GameState::MapPlayerIDAndTank vehicles;
        for (auto it = json["vehicles"].begin(); it != json["vehicles"].end();
             ++it)
        {
            std::vector<std::shared_ptr<AbstractTank>> tanks;
            int                                        player_id;
            it.value().at("player_id").get_to<int>(player_id);
            if (vehicles.find(player_id) != vehicles.end())
            {
                tanks = vehicles[player_id];
            }

            nlohmann::json vehicleJson;
            vehicleJson[it.key()] = it.value();
            tanks.emplace_back(vehicleJson.get<AbstractTank*>());

            vehicles.erase(player_id);
            vehicles.insert(std::make_pair(player_id, tanks));
        }
        gameState.SetVehicles(vehicles);
    }
    catch (nlohmann::json::type_error& exception)
    {
        std::cout << exception.what() << std::endl << std::flush;
    }
    catch (nlohmann::json::out_of_range& exception)
    {
        std::cout << exception.what() << std::endl << std::flush;
    }
    catch (nlohmann::json::parse_error& exception)
    {
        std::cout << exception.what() << std::endl << std::flush;
    }
    catch (std::out_of_range& exception)
    {
        std::cout << exception.what() << std::endl << std::flush;
    }
    catch (std::invalid_argument& exception)
    {
        std::cout << exception.what() << std::endl << std::flush;
    }
}

void to_json(nlohmann::json& json, const WinPoints& winPoints)
{
    json = nlohmann::json{ "" };
}

void from_json(const nlohmann::json& json, WinPoints& winPoints)
{
    winPoints.capture = json.at("capture");
    winPoints.kill    = json.at("kill");
}
