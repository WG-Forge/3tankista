#pragma once

#include "abstract_tank.h"

class SpgTank : public AbstractTank
{
public:
    SpgTank(int vehicleId);
    virtual ~SpgTank();

    bool CanShoot(const Vector3i& point) const override;
    bool CanMove(const Vector3i& point) const override;
};