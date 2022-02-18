#include "models.h"
#include "utility/singleton.h"

void to_json(nlohmann::json& json, const LoginRequestModel& loginRequestModel)
{
    json = nlohmann::json{ { "name", loginRequestModel.name },
                           { "password", loginRequestModel.password },
                           { "game", loginRequestModel.game },
                           { "num_turns", loginRequestModel.numberTurns },
                           { "num_players", loginRequestModel.numberPlayers },
                           { "is_observer", loginRequestModel.isObserver } };
}

void from_json(const nlohmann::json& json, LoginRequestModel& loginRequestModel)
{
    json.at("name").get_to(loginRequestModel.name);
    json.at("password").get_to(loginRequestModel.password);
    json.at("game").get_to(loginRequestModel.game);
    json.at("num_turns").get_to(loginRequestModel.numberTurns);
    json.at("num_players").get_to(loginRequestModel.numberPlayers);
    json.at("is_observer").get_to(loginRequestModel.isObserver);
}

void to_json(nlohmann::json& json, const LoginResponseModel& loginResponseModel)
{
    json = nlohmann::json{ { "idx", loginResponseModel.index },
                           { "name", loginResponseModel.name },
                           { "is_observer", loginResponseModel.isObserver } };
}

void from_json(const nlohmann::json& json, LoginResponseModel& loginResponseModel)
{
    json.at("idx").get_to(loginResponseModel.index);
    json.at("name").get_to(loginResponseModel.name);
    json.at("is_observer").get_to(loginResponseModel.isObserver);
}

void to_json(nlohmann::json& json, const PlayerModel& playerModel)
{
    json = nlohmann::json{ { "idx", playerModel.idx },
                           { "name", playerModel.name },
                           { "is_observer", playerModel.isObserver } };
}

void from_json(const nlohmann::json& json, PlayerModel& playerModel)
{
    json.at("idx").get_to(playerModel.idx);
    json.at("name").get_to(playerModel.name);
    json.at("is_observer").get_to(playerModel.isObserver);
}

#include "utility/enum_parser.h"

void to_json(nlohmann::json& json, const TankModel& tankModel)
{
    EnumParser<TankType> enumParser;
    json = nlohmann::json{
        { "player_id", tankModel.playerId }, { "vehicle_type", enumParser.Enum2String(tankModel.vehicleType) },
        { "health", tankModel.health },      { "spawn_position", tankModel.spawnPosition },
        { "position", tankModel.position },  { "capture_points", tankModel.capturePoints }
    };
}

void from_json(const nlohmann::json& json, TankModel& tankModel)
{
    EnumParser<TankType> enumParser;
    json.at("player_id").get_to(tankModel.playerId);
    tankModel.vehicleType = enumParser.String2Enum(json.at("vehicle_type"));
    json.at("health").get_to(tankModel.health);
    json.at("spawn_position").get_to(tankModel.spawnPosition);
    json.at("position").get_to(tankModel.position);
    json.at("capture_points").get_to(tankModel.capturePoints);
}

void to_json(nlohmann::json& json, const WinPointsModel& winPointsModel)
{
    json = nlohmann::json{ { "capture", winPointsModel.capture }, { "kill", winPointsModel.kill } };
}

void from_json(const nlohmann::json& json, WinPointsModel& winPointsModel)
{
    json.at("capture").get_to(winPointsModel.capture);
    json.at("kill").get_to(winPointsModel.kill);
}

void to_json(nlohmann::json& json, const GameStateModel& gameStateModel)
{
    json = nlohmann::json{
        { "num_players", gameStateModel.numberPlayers },  { "num_turns", gameStateModel.numberTurns },
        { "current_turn", gameStateModel.currentTurn },   { "players", gameStateModel.players },
        { "observers", gameStateModel.observers },        { "current_player_idx", gameStateModel.currentPlayerIndex },
        { "finished", gameStateModel.finished },          { "vehicles", gameStateModel.vehicles },
        { "attack_matrix", gameStateModel.attackMatrix }, { "winner", gameStateModel.winner },
        { "win_points", gameStateModel.winPoints }
    };
}

void from_json(const nlohmann::json& json, GameStateModel& gameStateModel)
{
    json.at("num_players").get_to(gameStateModel.numberPlayers);
    json.at("num_turns").get_to(gameStateModel.numberTurns);
    json.at("current_turn").get_to(gameStateModel.currentTurn);
    json.at("players").get_to(gameStateModel.players);
    json.at("observers").get_to(gameStateModel.observers);
    json.at("finished").get_to(gameStateModel.finished);
    std::vector<std::pair<int, TankModel>> vehicles;
    for (const auto& [key, value] : json["vehicles"].items())
    {
        TankModel model;
        from_json(value, model);
        vehicles.emplace_back(std::make_pair(std::stoi(key), model));
    }
    gameStateModel.vehicles = std::move(vehicles);
    std::unordered_map<int, std::vector<int>> attackMatrix;
    for (const auto& [key, value] : json["attack_matrix"].items())
    {
        std::vector<int> ids(value);
        attackMatrix.insert(std::make_pair(std::stoi(key), ids));
    }
    gameStateModel.attackMatrix = std::move(attackMatrix);
    if (json.at("current_player_idx").empty())
    {
        gameStateModel.currentPlayerIndex = 0;
    }
    else
    {
        json.at("current_player_idx").get_to(gameStateModel.currentPlayerIndex);
    }
    if (json.at("winner").empty())
    {
        gameStateModel.winner = 0;
    }
    else
    {
        json.at("winner").get_to(gameStateModel.winner);
    }
    std::unordered_map<int, WinPointsModel> winPoints;
    for (const auto& [key, value] : json["win_points"].items())
    {
        WinPointsModel tempwp{};
        from_json(value, tempwp);
        winPoints.insert(std::make_pair(std::stoi(key), tempwp));
    }
    gameStateModel.winPoints = std::move(winPoints);
}

void to_json(nlohmann::json& json, const ShootModel& shootModel)
{
    json = nlohmann::json{ { "vehicle_id", shootModel.vehicleId }, { "target", shootModel.target } };
}

void from_json(const nlohmann::json& json, ShootModel& shootModel)
{
    json.at("vehicle_id").get_to(shootModel.vehicleId);
    json.at("target").get_to(shootModel.target);
}

void to_json(nlohmann::json& json, const MoveModel& moveModel)
{
    json = nlohmann::json{ { "vehicle_id", moveModel.vehicleId }, { "target", moveModel.target } };
}

void from_json(const nlohmann::json& json, MoveModel& moveModel)
{
    json.at("vehicle_id").get_to(moveModel.vehicleId);
    json.at("target").get_to(moveModel.target);
}

void to_json(nlohmann::json& json, const ChatModel& chatModel)
{
    json = nlohmann::json{ { "message", chatModel.message } };
}

void from_json(const nlohmann::json& json, ChatModel& chatModel)
{
    json.at("message").get_to(chatModel.message);
}

void to_json(nlohmann::json& json, const ActionModel& actionModel)
{
    switch (actionModel.actionType)
    {
        case Action::CHAT:
        {
            json = nlohmann::json{ { "player_id", actionModel.playerIndex },
                                   { "action_type", (int)actionModel.actionType },
                                   { "data", std::get<ChatModel>(actionModel.data) } };
            break;
        }
        case Action::MOVE:
        {
            json = nlohmann::json{ { "player_id", actionModel.playerIndex },
                                   { "action_type", (int)actionModel.actionType },
                                   { "data", std::get<MoveModel>(actionModel.data) } };
            break;
        }
        case Action::SHOOT:
        {
            json = nlohmann::json{ { "player_id", actionModel.playerIndex },
                                   { "action_type", (int)actionModel.actionType },
                                   { "data", std::get<ShootModel>(actionModel.data) } };
            break;
        }
        default:
            break;
    }
}

void from_json(const nlohmann::json& json, ActionModel& actionModel)
{
    json.at("player_id").get_to(actionModel.playerIndex);
    actionModel.actionType = (Action)json.at("action_type").get<int>();
    switch (actionModel.actionType)
    {
        case Action::CHAT:
        {
            actionModel.data = json.at("data").get<ChatModel>();
            break;
        }
        case Action::MOVE:
        {
            actionModel.data = json.at("data").get<MoveModel>();
            break;
        }
        case Action::SHOOT:
        {
            actionModel.data = json.at("data").get<ShootModel>();
            break;
        }
        default:
            break;
    }
}

void to_json(nlohmann::json& json, const GameActionsModel& gameActionsModel)
{
    json = nlohmann::json{ { "actions", gameActionsModel.actions } };
}

void from_json(const nlohmann::json& json, GameActionsModel& gameActionsModel)
{
    json.at("actions").get_to(gameActionsModel.actions);
}

void to_json(nlohmann::json& json, const SpawnPointsModel& spawnPointsModel)
{
    json = nlohmann::json{ "" };
}

void from_json(const nlohmann::json& json, SpawnPointsModel& spawnPointsModel)
{
    for (const auto& [key, value] : json.items())
    {
        std::vector<Vector3i> positions;
        json.at(key).get_to<std::vector<Vector3i>>(positions);
        spawnPointsModel.spawnPoints.emplace_back(std::make_pair<TankType, std::vector<Vector3i>>(
            SINGLETON(EnumParser<TankType>)->String2Enum(key), std::move(positions)));
    }
}

void to_json(nlohmann::json& json, const MapModel& mapModel)
{
    json = nlohmann::json{ "" };
}

void from_json(const nlohmann::json& json, MapModel& mapModel)
{
    try
    {
        mapModel.size = json.at("size");
        json.at("name").get_to<std::string>(mapModel.name);
        nlohmann::json jsonContent = json.at("content");
        jsonContent.at("base").get_to<std::vector<Vector3i>>(mapModel.base);
        jsonContent.at("obstacle").get_to<std::vector<Vector3i>>(mapModel.obstacle);
        json.at("spawn_points").get_to<std::vector<SpawnPointsModel>>(mapModel.mapSpawnPoints);
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
}
