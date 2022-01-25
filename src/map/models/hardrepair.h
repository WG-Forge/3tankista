#ifndef HARDREPAIR_H
#define HARDREPAIR_H

#include "repair.h"

struct HardRepair : public Repair
{
    HardRepair();
    virtual ~HardRepair();
};

void to_json(nlohmann::json& j, const HardRepair& m);

void from_json(const nlohmann::json& j, HardRepair& m);

#endif // HARDREPAIR_H
