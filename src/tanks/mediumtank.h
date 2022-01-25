#ifndef SERVER_MEDIUMTANK_H
#define SERVER_MEDIUMTANK_H

#include "abstracttank.h"

class MediumTank : public AbstractTank
{
public:
    MediumTank(int vehicleId, Player *owner);
    ~MediumTank();

    // TODO: Implement CanHit method
    bool CanHit(const Vector3d& point) const override;
};

#endif // SERVER_MEDIUMTANK_H
