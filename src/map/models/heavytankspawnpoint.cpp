#include "heavytankspawnpoint.h"

HeavyTankSpawnPoint::HeavyTankSpawnPoint() {}

HeavyTankSpawnPoint::~HeavyTankSpawnPoint() {}

void to_json(nlohmann::json& j, const HeavyTankSpawnPoint& m)
{
    j = nlohmann::json{ "" };
}

void from_json(const nlohmann::json& j, HeavyTankSpawnPoint& m)
{
    m.SetTankType(TankType::Heavy);
    j.at("x").get_to(m.GetSpawnPoint().x());
    j.at("y").get_to(m.GetSpawnPoint().y());
    j.at("z").get_to(m.GetSpawnPoint().z());
}
