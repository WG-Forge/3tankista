#ifndef SERVER_TANKFACTORY_H
#define SERVER_TANKFACTORY_H

#include "abstracttankfactory.h"
#include "mediumtank.h"

class TankFactory : public AbstractTankFactory
{
public:
    TankFactory() {}
    virtual ~TankFactory() {}

    AbstractTank* CreateMediumTank(int vehicleId) const override
    {
        return (AbstractTank*)new MediumTank(vehicleId);
    }
};

#endif // SERVER_TANKFACTORY_H
