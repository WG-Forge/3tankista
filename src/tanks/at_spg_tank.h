#pragma once

#include "abstract_tank.h"

class AtSpgTank : public AbstractTank
{
public:
    AtSpgTank(int vehicleId);
    virtual ~AtSpgTank();

    void Shoot(const Vector3i& point) override;

    bool CanShoot(const Vector3i& point) const override;
    bool CanMove(const Vector3i& point) const override;
};
