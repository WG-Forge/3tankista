#ifndef SERVER_ABSTRACTTANKFACTORY_H
#define SERVER_ABSTRACTTANKFACTORY_H

#include "abstracttank.h"

class AbstractTankFactory
{
public:
    AbstractTankFactory() {}
    virtual ~AbstractTankFactory() {}

    virtual AbstractTank* CreateMediumTank(int vehicleId) const = 0;
    virtual AbstractTank* CreateAtSpgTank(int vehicleId) const = 0;
    virtual AbstractTank* CreateSpgTank(int vehicleId) const = 0;
    virtual AbstractTank* CreateHeavyTank(int vehicleId) const = 0;
    virtual AbstractTank* CreateLightTank(int vehicleId) const = 0;
};

#endif // SERVER_ABSTRACTTANKFACTORY_H
