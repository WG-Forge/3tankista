#ifndef LIGHTREPAIR_H
#define LIGHTREPAIR_H

#include "repair.h"

struct LightRepair : public Repair
{
    LightRepair();
    virtual ~LightRepair();
};

void to_json(nlohmann::json& j, const LightRepair& m);

void from_json(const nlohmann::json& j, LightRepair& m);

#endif // LIGHTREPAIR_H
