#include "atspgtankspawnpoint.h"

AtSpgTankSpawnPoint::AtSpgTankSpawnPoint() {}

AtSpgTankSpawnPoint::~AtSpgTankSpawnPoint() {}

void to_json(nlohmann::json& j, const AtSpgTankSpawnPoint& m)
{
    j = nlohmann::json{ "" };
}

void from_json(const nlohmann::json& j, AtSpgTankSpawnPoint& m)
{
    m.SetTankType(TankType::AtSpg);
    j.at("x").get_to(m.GetSpawnPoint().x());
    j.at("y").get_to(m.GetSpawnPoint().y());
    j.at("z").get_to(m.GetSpawnPoint().z());
}
