#include "spgtankspawnpoint.h"

SpgTankSpawnPoint::SpgTankSpawnPoint() {}

SpgTankSpawnPoint::~SpgTankSpawnPoint() {}

void to_json(nlohmann::json& j, const SpgTankSpawnPoint& m)
{
    j = nlohmann::json{ "" };
}

void from_json(const nlohmann::json& j, SpgTankSpawnPoint& m)
{
    m.SetTankType(TankType::Spg);
    j.at("x").get_to(m.GetSpawnPoint().x());
    j.at("y").get_to(m.GetSpawnPoint().y());
    j.at("z").get_to(m.GetSpawnPoint().z());
}
