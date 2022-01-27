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
    uint64_t    numberTurns;
    uint64_t    numberPlayers;
    bool        isObserver;
};

void to_json(nlohmann::json& json, const LoginRequestModel& loginRequestModel);

void from_json(const nlohmann::json& json,
               LoginRequestModel&    loginRequestModel);

} // namespace ServerModels

#endif // LOGINREQUESTMODEL_H
