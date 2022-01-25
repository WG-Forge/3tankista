#ifndef SERVER_TANKFACTORY_H
#define SERVER_TANKFACTORY_H

#include "abstracttankfactory.h"
#include "../mediumtank.h"

class TankFactory : public AbstractTankFactory
{
    AbstractTank *CreateMediumTank(int vehicleId, Player *owner) const override { return (AbstractTank *) new MediumTank(vehicleId, owner); }
};

#endif // SERVER_TANKFACTORY_H
