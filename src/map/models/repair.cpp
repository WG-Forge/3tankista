#include "repair.h"

Repair::Repair()
    : power(RepairPower::Light)
{
}

void to_json(nlohmann::json& j, const Repair& m)
{
    //    j = m.GetPower() == Repair::RepairPower::Light ?
    //        nlohmann::json{ "" } : nlohmann::json{ "" };
}

void from_json(const nlohmann::json& j, Repair& m) {}
