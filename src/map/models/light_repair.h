#pragma once

#include "repair.h"

struct LightRepair : public Repair
{
    LightRepair();
    virtual ~LightRepair();
};

void to_json(nlohmann::json& json, const LightRepair& lightRepair);

void from_json(const nlohmann::json& json, LightRepair& lightRepair);
