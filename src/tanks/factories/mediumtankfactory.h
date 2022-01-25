#ifndef SERVER_MEDIUMTANKFACTORY_H
#define SERVER_MEDIUMTANKFACTORY_H

#include "abstractfactory.h"
#include "../mediumtank.h"

class MediumTankFactory : public AbstractFactory
{
    AbstractTank *CreateTank(int vehicleId, Player *owner) const override { return (AbstractTank *) new MediumTank(vehicleId, owner); }
};

#endif // SERVER_MEDIUMTANKFACTORY_H
