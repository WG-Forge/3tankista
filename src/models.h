#pragma once

#include <string>

#include "nlohmann/json.hpp"

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

struct LoginResponceModel
{
    uint64_t    index;
    std::string name;
    bool        isObserver;
};

void to_json(nlohmann::json&           json,
             const LoginResponceModel& loginResponceModel);

void from_json(const nlohmann::json& json,
               LoginResponceModel&   loginResponceModel);
