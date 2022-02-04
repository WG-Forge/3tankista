#pragma once

#include "abstract_tank.h"

class HeavyTank : public AbstractTank
{
public:
    HeavyTank(int vehicleId);
    virtual ~HeavyTank();

    bool CanShoot(const Vector3i& point) const override;
    bool CanMove(const Vector3i& point) const override;
};
