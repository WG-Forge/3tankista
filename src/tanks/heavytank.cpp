#include "heavytank.h"

HeavyTank::HeavyTank(int vehicleId)
    : AbstractTank(vehicleId, TankType::HEAVY)
{
    SetHealth(3);
    SetMaxHealth(3);
    SetSpeed(1);
    SetDamage(1);
    SetDestructionPoints(3);
}

bool HeavyTank::CanShoot(const Vector3i& point) const
{
    return GameArea::GetDistance(point, this->GetPosition()) <= 2 &&
           GameArea::GetDistance(point, this->GetPosition()) > 0;
}

bool HeavyTank::CanMove(const Vector3i& point) const
{
    return GameArea::GetDistance(point, this->GetPosition()) <=
           this->GetSpeed();
}
