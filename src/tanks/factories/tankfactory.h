#ifndef SERVER_TANKFACTORY_H
#define SERVER_TANKFACTORY_H

#include "../mediumtank.h"
#include "abstracttankfactory.h"

class TankFactory : public AbstractTankFactory
{
    AbstractTank* CreateMediumTank(int vehicleId) const override
    {
        return (AbstractTank*)new MediumTank(vehicleId);
    }
};

#endif // SERVER_TANKFACTORY_H
