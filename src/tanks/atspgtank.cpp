#include "atspgtank.h"
#include "globalgameactions.h"

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

    int      distance = GameArea::GetDistance(point, this->GetPosition());
    Vector3i delta    = { point.x() - this->GetPosition().x(),
                       point.y() - this->GetPosition().y(),
                       point.z() - this->GetPosition().z() };
    Vector3i target;
    /*Vector3i deltaSign = { (delta.x() > 0) - (delta.x() < 0),
                           (delta.y() > 0) - (delta.y() < 0),
                           (delta.z() > 0) - (delta.z() < 0) };*/
    delta.x() > 0   ? target.x()   = delta.x() - distance + 1
    : delta.x() < 0 ? target.x() = delta.x() + distance - 1
                    : target.x() = this->GetPosition().x();
    delta.y() > 0   ? target.y()   = delta.y() - distance + 1
    : delta.y() < 0 ? target.y() = delta.y() + distance - 1
                    : target.y() = this->GetPosition().y();
    delta.z() > 0   ? target.z()   = delta.z() - distance + 1
    : delta.z() < 0 ? target.z() = delta.z() + distance - 1
                    : target.z() = this->GetPosition().z();
    SendShootAction(this->GetVehicleId(), target);
}
