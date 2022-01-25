#include "lighttankspawnpoint.h"

LightTankSpawnPoint::LightTankSpawnPoint() {}

LightTankSpawnPoint::~LightTankSpawnPoint() {}

void to_json(nlohmann::json& j, const LightTankSpawnPoint& m)
{
    j = nlohmann::json{ "" };
}

void from_json(const nlohmann::json& j, LightTankSpawnPoint& m)
{
    m.SetTankType(TankType::Light);
    j.at("x").get_to(m.GetSpawnPoint().x());
    j.at("y").get_to(m.GetSpawnPoint().y());
    j.at("z").get_to(m.GetSpawnPoint().z());
}
