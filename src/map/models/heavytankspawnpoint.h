#ifndef HEAVYTANKSPAWNPOINT_H
#define HEAVYTANKSPAWNPOINT_H

#include "tankspawnpoint.h"

struct HeavyTankSpawnPoint : public TankSpawnPoint
{
    HeavyTankSpawnPoint();
    virtual ~HeavyTankSpawnPoint();
};

void to_json(nlohmann::json& j, const HeavyTankSpawnPoint& m);

void from_json(const nlohmann::json& j, HeavyTankSpawnPoint& m);

#endif // HEAVYTANKSPAWNPOINT_H
