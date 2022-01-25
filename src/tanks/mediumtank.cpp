#include "mediumtank.h"

MediumTank::MediumTank(int vehicleId, Player* owner)
    : AbstractTank(vehicleId, owner, TankType::MEDIUM_TANK)
{
    SetMaxHealth(2);
    SetSpeed(2);
    SetDamage(1);
    SetDestructionPoints(2);
}

MediumTank::~MediumTank()
{
}
