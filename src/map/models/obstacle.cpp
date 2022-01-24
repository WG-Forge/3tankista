#include "obstacle.h"

void to_json(nlohmann::json& j, const Obstacle& m)
{
    j = nlohmann::json{ "" };
}

void from_json(const nlohmann::json& j, Obstacle& m) {}
