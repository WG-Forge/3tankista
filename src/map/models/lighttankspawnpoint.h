#ifndef LIGHTTANKSPAWNPOINT_H
#define LIGHTTANKSPAWNPOINT_H

#include "tankspawnpoint.h"

struct LightTankSpawnPoint : public TankSpawnPoint
{
    LightTankSpawnPoint();
    virtual ~LightTankSpawnPoint();
};

void to_json(nlohmann::json& j, const LightTankSpawnPoint& m);

void from_json(const nlohmann::json& j, LightTankSpawnPoint& m);

#endif // LIGHTTANKSPAWNPOINT_H
