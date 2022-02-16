#include "spawn_points_model.h"

void to_json(nlohmann::json& json, const SpawnPointsModel& spawnPointsModel)
{
    json = nlohmann::json{ "" };
}

void from_json(const nlohmann::json& json, SpawnPointsModel& spawnPointsModel)
{
    for (const auto& [key, value] : json.items())
    {
        std::vector<Vector3i> positions;
        json.at(key).get_to<std::vector<Vector3i>>(positions);
        spawnPointsModel.spawnPoints.emplace_back(
            std::make_pair<TankType, std::vector<Vector3i>>(
                SINGLETON(EnumParser<TankType>)->String2Enum(key),
                std::move(positions)));
    }
}