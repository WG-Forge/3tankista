#include "hard_repair.h"

HardRepair::HardRepair()
    : Repair(RepairPower::Hard)
{
}

void to_json(nlohmann::json& json, const HardRepair& hardRepair)
{
    json = nlohmann::json{ "" };
}

void from_json(const nlohmann::json& json, HardRepair& hardRepair)
{
    hardRepair.SetPower(Repair::RepairPower::Hard);
}
