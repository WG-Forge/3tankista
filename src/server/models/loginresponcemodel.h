#ifndef LOGINRESPONCEMODEL_H
#define LOGINRESPONCEMODEL_H

#include "nlohmann/json.hpp"

namespace ServerModels
{

struct LoginResponceModel
{
    uint64_t    idx;
    std::string name;
    std::string password;
    bool        isObserver;
};

void to_json(nlohmann::json& j, const LoginResponceModel& m);

void from_json(const nlohmann::json& j, LoginResponceModel& m);

using ClientDataModel = LoginResponceModel;

} // namespace ServerModels

#endif // LOGINRESPONCEMODEL_H
