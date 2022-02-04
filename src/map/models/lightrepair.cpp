#include "lightrepair.h"

LightRepair::LightRepair()
    : Repair(RepairPower::Light)
{
}

void to_json(nlohmann::json& json, const LightRepair& lightRepair)
{
    json = nlohmann::json{ "" };
}

void from_json(const nlohmann::json& json, LightRepair& lightRepair)
{
    lightRepair.SetPower(Repair::RepairPower::Light);
}
