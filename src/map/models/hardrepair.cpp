#include "hardrepair.h"

HardRepair::HardRepair()
    : Repair(RepairPower::Hard)
{
}

HardRepair::~HardRepair() {}

void to_json(nlohmann::json& j, const HardRepair& m)
{
    j = nlohmann::json{ "" };
}

void from_json(const nlohmann::json& j, HardRepair& m)
{
    m.SetPower(Repair::RepairPower::Hard);
}
