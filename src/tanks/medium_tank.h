#pragma once

#include "abstract_tank.h"

class MediumTank : public AbstractTank
{
public:
    MediumTank(int vehicleId);
    virtual ~MediumTank();

    bool CanShoot(const Vector3i& point) const override;
    bool CanMove(const Vector3i& point) const override;
};
