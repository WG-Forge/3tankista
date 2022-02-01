#ifndef SERVER_ATSPGTANK_H
#define SERVER_ATSPGTANK_H

#include "abstracttank.h"
#include "gamearea.h"
class AtSpgTank : public AbstractTank
{
public:
    AtSpgTank(int vehicleId);
    virtual ~AtSpgTank();

    bool CanShoot(const Vector3i& point) const override;
    bool CanMove(const Vector3i& point) const override;
};

#endif // SERVER_ATSPGTANK_H
