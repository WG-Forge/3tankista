#include "tankspawnpoint.h"

TankSpawnPoint::TankSpawnPoint()
    : playerId(0)
    , type(TankType::Medium)
    , spawnPoint(0.0, 0.0, 0.0)
{
}

void to_json(nlohmann::json& j, const TankSpawnPoint& m) {}

void from_json(const nlohmann::json& j, TankSpawnPoint& m)
{
    j.at("x").get_to(m.GetSpawnPoint().x());
    j.at("y").get_to(m.GetSpawnPoint().y());
    j.at("z").get_to(m.GetSpawnPoint().z());
}
