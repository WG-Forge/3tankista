#pragma once

#include "abstract_tank_factory.h"
#include "tanks/at_spg_tank.h"
#include "tanks/heavy_tank.h"
#include "tanks/light_tank.h"
#include "tanks/medium_tank.h"
#include "tanks/spg_tank.h"

class TankFactory : public AbstractTankFactory
{
public:
    TankFactory() {}
    virtual ~TankFactory() {}

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
