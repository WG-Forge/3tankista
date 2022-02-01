#include "spgtank.h"

SpgTank::SpgTank(int vehicleId)
    : AbstractTank(vehicleId, TankType::SPG)
{
    SetHealth(2);
    SetMaxHealth(2);
    SetSpeed(1);
    SetDamage(1);
    SetDestructionPoints(2);
}

SpgTank::~SpgTank() {}

bool SpgTank::CanShoot(const Vector3i& point) const
{
    bool canShoot = false;
    if (GameArea::GetDistance(point, this->GetPosition()) != 1)
    {
        if (GameArea::GetDistance(point, this->GetPosition()) <= 3)
        {
            if (point.x() == this->GetPosition().x() ||
                point.y() == this->GetPosition().y() ||
                point.z() == this->GetPosition().z())
            {
                canShoot = true;
            }
        }
    }
    else
    {
        canShoot = true;
    }
    return canShoot;
}

bool SpgTank::CanMove(const Vector3i& point) const
{
    return GameArea::GetDistance(point, this->GetPosition()) <=
           this->GetSpeed();
}
