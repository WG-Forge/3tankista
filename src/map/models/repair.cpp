#include "repair.h"

Repair::Repair()
    : power(RepairPower::Undefined)
{
}

Repair::Repair(const RepairPower power)
    : power(power)
{
}

void to_json(nlohmann::json& json, const Repair& repair)
{
    json = nlohmann::json{ "" };
}

void from_json(const nlohmann::json& json, Repair& repair) {}
