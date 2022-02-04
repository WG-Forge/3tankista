#pragma once

#include "nlohmann/json.hpp"

struct Obstacle
{
};

void to_json(nlohmann::json& json, const Obstacle& obstacle);

void from_json(const nlohmann::json& json, Obstacle& obstacle);
