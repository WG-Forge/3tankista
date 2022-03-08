#pragma once

#include "components/ttc_component.h"
#include "ecs.h"
#include "game/game_events.h"
#include "ttc.h"

class AbstractFactory
{
public:
    AbstractFactory()          = default;
    virtual ~AbstractFactory() = default;

    virtual TtcComponent* CreateMediumTankTtc(GameObjectId id) const = 0;
    virtual TtcComponent* CreateAtSpgTankTtc(GameObjectId id) const  = 0;
    virtual TtcComponent* CreateSpgTankTtc(GameObjectId id) const    = 0;
    virtual TtcComponent* CreateHeavyTankTtc(GameObjectId id) const  = 0;
    virtual TtcComponent* CreateLightTankTtc(GameObjectId id) const  = 0;

    TtcComponent* CreateTtc(GameObjectId id, const Ttc& ttc) const;
};
