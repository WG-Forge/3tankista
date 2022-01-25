#include "mediumtank.h"

MediumTank::MediumTank(int vehicleId, Player* owner)
    : AbstractTank(vehicleId, owner, TankType::MEDIUM_TANK)
{
    SetHealth(2);
}

MediumTank::~MediumTank()
{
}
