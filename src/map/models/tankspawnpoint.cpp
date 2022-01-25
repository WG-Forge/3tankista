#include "tankspawnpoint.h"

TankSpawnPoint::TankSpawnPoint()
    : type(TankType::Medium)
    , spawnPoint(0.0, 0.0, 0.0)
{
}

TankSpawnPoint::~TankSpawnPoint() {}

void to_json(nlohmann::json& j, const TankSpawnPoint& m)
{
    j = nlohmann::json{ "" };
}

void from_json(const nlohmann::json& j, TankSpawnPoint& m)
{
    m.SetTankType(TankType::Medium);
    j.at("x").get_to(m.GetSpawnPoint().x());
    j.at("y").get_to(m.GetSpawnPoint().y());
    j.at("z").get_to(m.GetSpawnPoint().z());
}
