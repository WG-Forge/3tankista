#include "hardrepair.h"

HardRepair::HardRepair()
    : Repair(RepairPower::Hard)
{
}

HardRepair::~HardRepair() {}

void to_json(nlohmann::json& json, const HardRepair& hardRepair)
{
    json = nlohmann::json{ "" };
}

void from_json(const nlohmann::json& json, HardRepair& hardRepair)
{
    hardRepair.SetPower(Repair::RepairPower::Hard);
}
