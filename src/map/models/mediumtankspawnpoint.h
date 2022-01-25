#ifndef MEDIUMTANKSPAWNPOINT_H
#define MEDIUMTANKSPAWNPOINT_H

#include "tankspawnpoint.h"

struct MediumTankSpawnPoint : public TankSpawnPoint
{
    MediumTankSpawnPoint();
    virtual ~MediumTankSpawnPoint();
};

void to_json(nlohmann::json& j, const MediumTankSpawnPoint& m);

void from_json(const nlohmann::json& j, MediumTankSpawnPoint& m);

#endif // MEDIUMTANKSPAWNPOINT_H
