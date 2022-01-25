#ifndef SERVER_MEDIUMTANK_H
#define SERVER_MEDIUMTANK_H

#include "abstracttank.h"

class MediumTank : public AbstractTank
{
public:
    MediumTank(int vehicleId);
    ~MediumTank();

    // TODO: Implement methods
    bool CanShoot(const Vector3i& point) const override;
    bool CanMove(const Vector3i& point) const override;
};

#endif // SERVER_MEDIUMTANK_H
