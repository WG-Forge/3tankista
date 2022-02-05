#pragma once

#include "abstract_tank.h"

class LightTank : public AbstractTank
{
public:
    explicit LightTank(int vehicleId);
    ~LightTank() override = default;

    bool CanShoot(const Vector3i& point) const override;
    bool CanMove(const Vector3i& point) const override;
};
