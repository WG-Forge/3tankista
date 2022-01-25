#ifndef ATSPGTANKSPAWNPOINT_H
#define ATSPGTANKSPAWNPOINT_H

#include "tankspawnpoint.h"

struct AtSpgTankSpawnPoint : public TankSpawnPoint
{
    AtSpgTankSpawnPoint();
    virtual ~AtSpgTankSpawnPoint();
};

void to_json(nlohmann::json& j, const AtSpgTankSpawnPoint& m);

void from_json(const nlohmann::json& j, AtSpgTankSpawnPoint& m);

#endif // ATSPGTANKSPAWNPOINT_H
