#pragma once

#include "abstract_tank.h"

class MediumTank : public AbstractTank
{
public:
    explicit MediumTank(int vehicleId);
    ~MediumTank() override = default;

    bool CanShoot(const Vector3i& point) const override;
    bool CanMove(const Vector3i& point) const override;
};
