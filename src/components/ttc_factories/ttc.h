#pragma once

#include "utility/tank_types.h"

struct Ttc
{
    int      speed;
    int      maxHealth;
    TankType tankType;
    int      damage;
};

constexpr Ttc SPG_TANK_TTC    = { 1, 1, TankType::SPG, 1 };
constexpr Ttc LIGHT_TANK_TTC  = { 3, 1, TankType::LIGHT, 1 };
constexpr Ttc HEAVY_TANK_TTC  = { 1, 3, TankType::HEAVY, 1 };
constexpr Ttc MEDIUM_TANK_TTC = { 2, 2, TankType::MEDIUM, 1 };
constexpr Ttc AT_SPG_TANK_TTC = { 1, 2, TankType::NO_TYPE, 1 };
