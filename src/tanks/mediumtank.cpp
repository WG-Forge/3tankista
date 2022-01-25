#include "mediumtank.h"

MediumTank::MediumTank(int vehicleId)
    : AbstractTank(vehicleId, TankType::MEDIUM)
{
    SetMaxHealth(2);
    SetSpeed(2);
    SetDamage(1);
    SetDestructionPoints(2);
}

MediumTank::~MediumTank()
{
}
