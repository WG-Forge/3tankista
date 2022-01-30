#include "mediumtank.h"
#include "gamearea.h"

MediumTank::MediumTank(int vehicleId)
    : AbstractTank(vehicleId, TankType::MEDIUM)
{
    SetHealth(2);
    SetMaxHealth(2);
    SetSpeed(2);
    SetDamage(1);
    SetDestructionPoints(2);
}

MediumTank::~MediumTank() {}

bool MediumTank::CanShoot(const Vector3i& point) const
{
    return GameArea::GetDistance(point, this->GetPosition()) == 2;
}

bool MediumTank::CanMove(const Vector3i& point) const
{
    return GameArea::GetDistance(point, this->GetPosition()) <= this->GetSpeed();
}
