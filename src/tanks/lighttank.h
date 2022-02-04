#ifndef SERVER_LIGHTTANK_H
#define SERVER_LIGHTTANK_H

#include "abstracttank.h"
#include "gamearea.h"
class LightTank : public AbstractTank
{
public:
    explicit LightTank(int vehicleId);
    ~LightTank() override =default;

    bool CanShoot(const Vector3i& point) const override;
    bool CanMove(const Vector3i& point) const override;
};

#endif // SERVER_LIGHTTANK_H
