#pragma once
#include "utility/enum_parser.h"
#include "utility/matrix.hpp"
#include "utility/singleton.h"
#include "utility/tank_types.h"

struct SpawnPointsModel
{
    std::vector<std::pair<TankType, std::vector<Vector3i>>> spawnPoints;
};

void to_json(nlohmann::json& json, const SpawnPointsModel& spawnPointsModel);

void from_json(const nlohmann::json& json, SpawnPointsModel& spawnPointsModel);
