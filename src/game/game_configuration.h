#pragma once

#include "components/ttc_factories/ttc.h"

static constexpr float DELTA_TIME_STEP{ 1.0f / 60.0f };

constexpr Ttc SPG_TANK_TTC                = { 1, 1, TankType::SPG, 1 };
constexpr Ttc LIGHT_TANK_TTC              = { 3, 1, TankType::LIGHT, 1 };
constexpr Ttc HEAVY_TANK_TTC              = { 1, 3, TankType::HEAVY, 1 };
constexpr Ttc MEDIUM_TANK_TTC             = { 2, 2, TankType::MEDIUM, 1 };
constexpr Ttc AT_SPG_TANK_TTC             = { 1, 2, TankType::NO_TYPE, 1 };
constexpr int MEDIUM_TANK_DAMAGE_DISTANCE = 2;
constexpr int HEAVY_TANK_DAMAGE_DISTANCE = 2;
constexpr int LIGHT_TANK_DAMAGE_DISTANCE = 2;
constexpr int SPG_TANK_DAMAGE_DISTANCE = 3;
constexpr int AT_SPG_TANK_DAMAGE_DISTANCE = 3;
