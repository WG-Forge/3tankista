#pragma once

#include "abstract_tank.h"

class SpgTank : public AbstractTank
{
public:
    explicit SpgTank(int vehicleId);
    ~SpgTank() override = default;

    bool CanShoot(const Vector3i& point) const override;
    bool CanMove(const Vector3i& point) const override;
};