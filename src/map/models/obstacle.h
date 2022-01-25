#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "nlohmann/json.hpp"

struct Obstacle
{
};

void to_json(nlohmann::json& j, const Obstacle& m);

void from_json(const nlohmann::json& j, Obstacle& m);

#endif // OBSTACLE_H
