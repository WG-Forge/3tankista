#pragma once

#include "abstract_factory.h"

class TtcComponentFactory : public AbstractFactory
{
public:
    TtcComponentFactory()           = default;
    ~TtcComponentFactory() override = default;

    TtcComponent* CreateAtSpgTankTtc(GameObjectId id) const override
    {
        return CreateTtc(id, AT_SPG_TANK_TTC);
    }

    TtcComponent* CreateHeavyTankTtc(GameObjectId id) const override
    {
        return CreateTtc(id, HEAVY_TANK_TTC);
    }

    TtcComponent* CreateLightTankTtc(GameObjectId id) const override
    {
        return CreateTtc(id, LIGHT_TANK_TTC);
    }

    TtcComponent* CreateMediumTankTtc(GameObjectId id) const override
    {
        return CreateTtc(id, MEDIUM_TANK_TTC);
    }

    TtcComponent* CreateSpgTankTtc(GameObjectId id) const override
    {
        return CreateTtc(id, SPG_TANK_TTC);
    }
};
