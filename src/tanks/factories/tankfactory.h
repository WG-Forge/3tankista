#ifndef SERVER_TANKFACTORY_H
#define SERVER_TANKFACTORY_H

#include "abstracttankfactory.h"
#include "atspgtank.h"
#include "heavytank.h"
#include "lighttank.h"
#include "mediumtank.h"
#include "spgtank.h"

class TankFactory : public AbstractTankFactory
{
public:
    TankFactory()          = default;
    virtual ~TankFactory() = default;

    AbstractTank* CreateMediumTank(int vehicleId) const override
    {
        return (AbstractTank*)new MediumTank(vehicleId);
    }
    AbstractTank* CreateAtSpgTank(int vehicleId) const override
    {
        return (AbstractTank*)new AtSpgTank(vehicleId);
    }
    AbstractTank* CreateSpgTank(int vehicleId) const override
    {
        return (AbstractTank*)new SpgTank(vehicleId);
    }
    AbstractTank* CreateHeavyTank(int vehicleId) const override
    {
        return (AbstractTank*)new HeavyTank(vehicleId);
    }
    AbstractTank* CreateLightTank(int vehicleId) const override
    {
        return (AbstractTank*)new LightTank(vehicleId);
    }
};

#endif // SERVER_TANKFACTORY_H
