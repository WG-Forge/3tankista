#pragma once

#include "components/ttc_factories/ttc.h"
#include "utility/matrix.hpp"

static constexpr float DELTA_TIME_STEP{ 1.0f / 60.0f };

constexpr Ttc SPG_TANK_TTC                = { 1, 1, TankType::SPG, 1 };
constexpr Ttc LIGHT_TANK_TTC              = { 3, 1, TankType::LIGHT, 1 };
constexpr Ttc HEAVY_TANK_TTC              = { 1, 3, TankType::HEAVY, 1 };
constexpr Ttc MEDIUM_TANK_TTC             = { 2, 2, TankType::MEDIUM, 1 };
constexpr Ttc AT_SPG_TANK_TTC             = { 1, 2, TankType::NO_TYPE, 1 };
constexpr int MEDIUM_TANK_DAMAGE_DISTANCE = 2;
constexpr int HEAVY_TANK_DAMAGE_DISTANCE  = 2;
constexpr int LIGHT_TANK_DAMAGE_DISTANCE  = 2;
constexpr int SPG_TANK_DAMAGE_DISTANCE    = 3;
constexpr int AT_SPG_TANK_DAMAGE_DISTANCE = 3;

static constexpr unsigned int GAME_WINDOW_WIDTH{ 800 };

static constexpr unsigned int GAME_WINDOW_HEIGHT{ 600 };

static constexpr bool GAME_WINDOW_FULLSCREEN{ false };

static constexpr std::size_t HEX_SIZE{ std::size_t(24 /*32 * 1.75*/) };

inline static const std::size_t LONG_DIAGONAL  = HEX_SIZE * std::sqrt(3) / 2.0; // 1/2 from short hex diagonal
inline static const std::size_t SHORT_DIAGONAL = HEX_SIZE / 2.0;                // 1/4 from long hex diagonal

inline static const Matrix2f GRID_BASIS{ { (float)SHORT_DIAGONAL, 0 }, { 0, (float)LONG_DIAGONAL } };
inline static const Matrix2f HEX_BASIS{
    { (GRID_BASIS.getCol(0) * 3 + GRID_BASIS.getCol(1)).x(), (GRID_BASIS.getCol(1) * 2).x() },
    { (GRID_BASIS.getCol(0) * 3 + GRID_BASIS.getCol(1)).y(), (GRID_BASIS.getCol(1) * 2).y() }
};
