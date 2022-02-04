#include "lighttank.h"

LightTank::LightTank(int vehicleId)
    : AbstractTank(vehicleId, TankType::LIGHT)
{
    SetHealth(1);
    SetMaxHealth(1);
    SetSpeed(3);
    SetDamage(1);
    SetDestructionPoints(1);
}

bool LightTank::CanShoot(const Vector3i& point) const
{
    return GameArea::GetDistance(point, this->GetPosition()) == 2;
}

bool LightTank::CanMove(const Vector3i& point) const
{
    return GameArea::GetDistance(point, this->GetPosition()) <=
           this->GetSpeed();
}
