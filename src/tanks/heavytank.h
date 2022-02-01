#ifndef SERVER_HEAVYTANK_H
#define SERVER_HEAVYTANK_H

#include "abstracttank.h"
#include "gamearea.h"
class HeavyTank : public AbstractTank
{
public:
    HeavyTank(int vehicleId);
    virtual ~HeavyTank();

    bool CanShoot(const Vector3i& point) const override;
    bool CanMove(const Vector3i& point) const override;
};
#endif // SERVER_HEAVYTANK_H
