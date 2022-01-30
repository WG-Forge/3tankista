#include "loginrequestmodel.h"

void ServerModels::to_json(nlohmann::json&          json,
                           const LoginRequestModel& loginRequestModel)
{
    json = nlohmann::json{ { "name", loginRequestModel.name },
                           { "password", loginRequestModel.password },
                           { "game", loginRequestModel.game },
                           { "num_turns", loginRequestModel.numberTurns },
                           { "num_players", loginRequestModel.numberPlayers },
                           { "is_observer", loginRequestModel.isObserver } };
}

void ServerModels::from_json(const nlohmann::json& json,
                             LoginRequestModel&    loginRequestModel)
{
    json.at("name").get_to(loginRequestModel.name);
    json.at("password").get_to(loginRequestModel.password);
    json.at("game").get_to(loginRequestModel.game);
    json.at("num_turns").get_to(loginRequestModel.numberTurns);
    json.at("num_players").get_to(loginRequestModel.numberPlayers);
    json.at("is_observer").get_to(loginRequestModel.isObserver);
}
