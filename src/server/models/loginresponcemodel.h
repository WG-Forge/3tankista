#ifndef LOGINRESPONCEMODEL_H
#define LOGINRESPONCEMODEL_H

#include "nlohmann/json.hpp"

namespace ServerModels
{

struct LoginResponceModel
{
    uint64_t    index;
    std::string name;
    std::string password;
    bool        isObserver;
};

void to_json(nlohmann::json&           json,
             const LoginResponceModel& loginResponceModel);

void from_json(const nlohmann::json& json,
               LoginResponceModel&   loginResponceModel);

using ClientDataModel = LoginResponceModel;

} // namespace ServerModels

#endif // LOGINRESPONCEMODEL_H
