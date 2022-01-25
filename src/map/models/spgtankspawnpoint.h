#ifndef SPGTANKSPAWNPOINT_H
#define SPGTANKSPAWNPOINT_H

#include "tankspawnpoint.h"

struct SpgTankSpawnPoint : public TankSpawnPoint
{
    SpgTankSpawnPoint();
    virtual ~SpgTankSpawnPoint();
};

void to_json(nlohmann::json& j, const SpgTankSpawnPoint& m);

void from_json(const nlohmann::json& j, SpgTankSpawnPoint& m);

#endif // SPGTANKSPAWNPOINT_H
