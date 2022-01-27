#include "obstacle.h"

void to_json(nlohmann::json& json, const Obstacle& obstacle)
{
    json = nlohmann::json{ "" };
}

void from_json(const nlohmann::json& json, Obstacle& obstacle) {}
