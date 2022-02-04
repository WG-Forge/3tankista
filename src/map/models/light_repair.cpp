#include "light_repair.h"

LightRepair::LightRepair()
    : Repair(RepairPower::Light)
{
}

LightRepair::~LightRepair() {}

void to_json(nlohmann::json& json, const LightRepair& lightRepair)
{
    json = nlohmann::json{ "" };
}

void from_json(const nlohmann::json& json, LightRepair& lightRepair)
{
    lightRepair.SetPower(Repair::RepairPower::Light);
}
