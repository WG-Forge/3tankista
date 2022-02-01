#include "atspgtank.h"

AtSpgTank::AtSpgTank(int vehicleId)
    : AbstractTank(vehicleId, TankType::AT_SPG)
{
    SetHealth(1);
    SetMaxHealth(1);
    SetSpeed(1);
    SetDamage(1);
    SetDestructionPoints(1);
}

AtSpgTank::~AtSpgTank() {}

bool AtSpgTank::CanShoot(const Vector3i& point) const
{
    return GameArea::GetDistance(point, this->GetPosition()) == 3;
}

bool AtSpgTank::CanMove(const Vector3i& point) const
{
    return GameArea::GetDistance(point, this->GetPosition()) <=
           this->GetSpeed();
}
