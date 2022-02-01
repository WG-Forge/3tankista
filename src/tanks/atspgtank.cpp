#include "atspgtank.h"

AtSpgTank::AtSpgTank(int vehicleId)
    : AbstractTank(vehicleId, TankType::AT_SPG)
{
    SetHealth(2);
    SetMaxHealth(2);
    SetSpeed(1);
    SetDamage(1);
    SetDestructionPoints(2);
}

AtSpgTank::~AtSpgTank() {}

bool AtSpgTank::CanShoot(const Vector3i& point) const
{
    return (GameArea::GetDistance(point, this->GetPosition()) <= 3) &&
           (point.x() == this->GetPosition().x() ||
            point.y() == this->GetPosition().y() ||
            point.z() == this->GetPosition().z());
}

bool AtSpgTank::CanMove(const Vector3i& point) const
{
    return GameArea::GetDistance(point, this->GetPosition()) <=
           this->GetSpeed();
}

void AtSpgTank::Shoot(const Vector3i& point)
{
    // TODO: Sergei write here
    AbstractTank::Shoot(point);
}
