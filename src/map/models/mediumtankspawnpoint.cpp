#include "mediumtankspawnpoint.h"

MediumTankSpawnPoint::MediumTankSpawnPoint() {}

MediumTankSpawnPoint::~MediumTankSpawnPoint() {}

void to_json(nlohmann::json& j, const MediumTankSpawnPoint& m)
{
    j = nlohmann::json{ "" };
}

void from_json(const nlohmann::json& j, MediumTankSpawnPoint& m)
{
    m.SetTankType(TankType::Medium);
    j.at("x").get_to(m.GetSpawnPoint().x());
    j.at("y").get_to(m.GetSpawnPoint().y());
    j.at("z").get_to(m.GetSpawnPoint().z());
}
