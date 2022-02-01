#ifndef SERVER_SPGTANK_H
#define SERVER_SPGTANK_H

#include "abstracttank.h"
#include "gamearea.h"
class SpgTank : public AbstractTank
{
public:
    SpgTank(int vehicleId);
    virtual ~SpgTank();

    bool CanShoot(const Vector3i& point) const override;
    bool CanMove(const Vector3i& point) const override;
};

#endif // SERVER_SPGTANK_H
