#include "loginrequestmodel.h"

void ServerModels::to_json(nlohmann::json& j, const LoginRequestModel& m)
{
    j = nlohmann::json{ { "name", m.name },
                        { "password", m.password },
                        { "game", m.game },
                        { "num_turns", m.numTurns },
                        { "num_players", m.numPlayers },
                        { "is_observer", m.isObserver } };
}

void ServerModels::from_json(const nlohmann::json& j, LoginRequestModel& m)
{
    j.at("name").get_to(m.name);
    j.at("password").get_to(m.password);
    j.at("game").get_to(m.game);
    j.at("num_turns").get_to(m.numTurns);
    j.at("num_players").get_to(m.numPlayers);
    j.at("is_observer").get_to(m.isObserver);
}
