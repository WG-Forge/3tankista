#ifndef LOGINREQUESTMODEL_H
#define LOGINREQUESTMODEL_H

#include "nlohmann/json.hpp"

namespace ServerModels
{

struct LoginRequestModel
{
    std::string name;
    std::string password;
    std::string game;
    uint64_t    numTurns;
    uint64_t    numPlayers;
    bool        isObserver;
};

void to_json(nlohmann::json& j, const LoginRequestModel& m);

void from_json(const nlohmann::json& j, LoginRequestModel& m);

} // namespace ServerModels

#endif // LOGINREQUESTMODEL_H
