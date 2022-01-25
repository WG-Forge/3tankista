#include "lightrepair.h"

LightRepair::LightRepair()
    : Repair(RepairPower::Light)
{
}

LightRepair::~LightRepair() {}

void to_json(nlohmann::json& j, const LightRepair& m)
{
    j = nlohmann::json{ "" };
}

void from_json(const nlohmann::json& j, LightRepair& m)
{
    m.SetPower(Repair::RepairPower::Light);
}
