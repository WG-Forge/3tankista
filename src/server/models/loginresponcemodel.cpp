#include "loginresponcemodel.h"

void ServerModels::to_json(nlohmann::json&           json,
                           const LoginResponceModel& loginResponceModel)
{
    json = nlohmann::json{ { "idx", loginResponceModel.index },
                           { "name", loginResponceModel.name },
                           { "password", loginResponceModel.password },
                           { "is_observer", loginResponceModel.isObserver } };
}

void ServerModels::from_json(const nlohmann::json& json,
                             LoginResponceModel&   loginResponceModel)
{
    json.at("idx").get_to(loginResponceModel.index);
    json.at("name").get_to(loginResponceModel.name);
    json.at("password").get_to(loginResponceModel.password);
    json.at("is_observer").get_to(loginResponceModel.isObserver);
}
