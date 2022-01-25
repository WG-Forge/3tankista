#include "repair.h"

Repair::Repair()
    : power(RepairPower::Undefined)
{
}

Repair::Repair(const RepairPower power)
    : power(power)
{
}

Repair::~Repair() {}

void to_json(nlohmann::json& j, const Repair& m)
{
    j = nlohmann::json{ "" };
}

void from_json(const nlohmann::json& j, Repair& m) {}
