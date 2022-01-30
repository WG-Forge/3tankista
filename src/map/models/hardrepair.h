#ifndef HARDREPAIR_H
#define HARDREPAIR_H

#include "repair.h"

struct HardRepair : public Repair
{
    HardRepair();
    virtual ~HardRepair();
};

void to_json(nlohmann::json& json, const HardRepair& hardRepair);

void from_json(const nlohmann::json& json, HardRepair& hardRepair);

#endif // HARDREPAIR_H
