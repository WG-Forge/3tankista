#pragma once
#include "spawn_points_model.h"
#include "utility/enum_parser.h"
#include "utility/matrix.hpp"
#include "utility/singleton.h"
#include "utility/tank_types.h"

struct MapModel
{
    std::vector<SpawnPointsModel> mapSpawnPoints;
    std::vector<Vector3i>         obstacle;
    std::vector<Vector3i>         base;
    int                           size;
    std::string                   name;
};

void to_json(nlohmann::json& json, const MapModel& mapModel);

void from_json(const nlohmann::json& json, MapModel& mapModel);
