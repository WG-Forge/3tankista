#pragma once

#include "abstract_tank.h"

class LightTank : public AbstractTank
{
public:
    LightTank(int vehicleId);
    virtual ~LightTank();

    bool CanShoot(const Vector3i& point) const override;
    bool CanMove(const Vector3i& point) const override;
};
