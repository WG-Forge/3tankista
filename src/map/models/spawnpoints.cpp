#include "spawnpoints.h"
#include "enumparser.h"
#include "singleton.h"

SpawnPoints::SpawnPoints()
/*: mediumTankSpawnPoints()*/ {}

void to_json(nlohmann::json& json, const SpawnPoints& spawnPoints)
{
    json = nlohmann::json{ "" };
}

void from_json(const nlohmann::json& json, SpawnPoints& spawnPoints)
{
    for (const auto& [key, value] : json.items())
    {
        std::vector<Vector3i> positions;
        json.at(key).get_to<std::vector<Vector3i>>(positions);
        spawnPoints.GetTanksSpawnPoints().emplace_back(
            std::make_pair<TankType, std::vector<Vector3i>>(
                SINGLETON(EnumParser<TankType>)->String2Enum(key),
                std::move(positions)));
    }
}
