#include "spawnpoints.h"

SpawnPoints::SpawnPoints()
    : spawnPoints()
{
}

void to_json(nlohmann::json& j, const SpawnPoints& m) {}

void from_json(const nlohmann::json& j, SpawnPoints& m)
{
    j.at("spawn_points")
        .get_to<std::vector<TankSpawnPoint>>(m.GetSpawnPoints());
}
