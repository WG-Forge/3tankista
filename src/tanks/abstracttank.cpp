#include "abstracttank.h"

AbstractTank::AbstractTank(int vehicleId, Player *owner, const TankType& tankType)
    : vehicleId(vehicleId)
    , player(owner)
    , tankType(tankType)
{
}

AbstractTank::~AbstractTank()
{
}
