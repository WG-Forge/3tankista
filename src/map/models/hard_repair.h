#pragma once

#include "repair.h"

struct HardRepair : public Repair
{
    HardRepair();
    ~HardRepair() override = default;
};

void to_json(nlohmann::json& json, const HardRepair& hardRepair);

void from_json(const nlohmann::json& json, HardRepair& hardRepair);
