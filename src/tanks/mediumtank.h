#ifndef SERVER_MEDIUMTANK_H
#define SERVER_MEDIUMTANK_H

#include "abstracttank.h"

class MediumTank : public AbstractTank
{
public:
    explicit MediumTank(int vehicleId);
    ~MediumTank() override = default;

    bool CanShoot(const Vector3i& point) const override;
    bool CanMove(const Vector3i& point) const override;
};

#endif // SERVER_MEDIUMTANK_H
