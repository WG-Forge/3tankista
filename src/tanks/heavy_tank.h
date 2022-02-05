#pragma once

#include "abstract_tank.h"

class HeavyTank : public AbstractTank
{
public:
    explicit HeavyTank(int vehicleId);
    ~HeavyTank() override = default;

    bool CanShoot(const Vector3i& point) const override;
    bool CanMove(const Vector3i& point) const override;
};
