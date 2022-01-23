#include "loginresponcemodel.h"

void ServerModels::to_json(nlohmann::json& j, const LoginResponceModel& m)
{
    j = nlohmann::json{ { "idx", m.idx },
                        { "name", m.name },
                        { "password", m.password },
                        { "is_observer", m.isObserver } };
}

void ServerModels::from_json(const nlohmann::json& j, LoginResponceModel& m)
{
    j.at("idx").get_to(m.idx);
    j.at("name").get_to(m.name);
    j.at("password").get_to(m.password);
    j.at("is_observer").get_to(m.isObserver);
}
