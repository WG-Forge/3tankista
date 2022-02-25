#pragma once

#include "components/ttc_factories/ttc.h"
#include "utility/matrix.hpp"

static constexpr float DELTA_TIME_STEP{ 1.0f / 60.0f };

constexpr Ttc SPG_TANK_TTC    = { 1, 1, TankType::SPG, 1, 3 };
constexpr Ttc LIGHT_TANK_TTC  = { 3, 1, TankType::LIGHT, 1, 2 };
constexpr Ttc HEAVY_TANK_TTC  = { 1, 3, TankType::HEAVY, 1, 2 };
constexpr Ttc MEDIUM_TANK_TTC = { 2, 2, TankType::MEDIUM, 1, 2 };
constexpr Ttc AT_SPG_TANK_TTC = { 1, 2, TankType::NO_TYPE, 1, 3 };

static constexpr unsigned int GAME_WINDOW_WIDTH{ 1920 };

static constexpr unsigned int GAME_WINDOW_HEIGHT{ 1080 };

static constexpr bool GAME_WINDOW_FULLSCREEN{ false };

static constexpr std::size_t HEX_SIZE{ std::size_t(GAME_WINDOW_WIDTH / 80 /*32 * 1.75*/) };

inline static const std::size_t LONG_DIAGONAL  = HEX_SIZE * std::sqrt(3) / 2.0; // 1/2 from short hex diagonal
inline static const std::size_t SHORT_DIAGONAL = HEX_SIZE / 2.0;                // 1/4 from long hex diagonal

inline static const Matrix2f GRID_BASIS{ { (float)SHORT_DIAGONAL, 0 }, { 0, (float)LONG_DIAGONAL } };
inline static const Matrix2f HEX_BASIS{
    { (GRID_BASIS.getCol(0) * 3 + GRID_BASIS.getCol(1)).x(), (GRID_BASIS.getCol(1) * 2).x() },
    { (GRID_BASIS.getCol(0) * 3 + GRID_BASIS.getCol(1)).y(), (GRID_BASIS.getCol(1) * 2).y() }
};

inline static const std::string AT_SPG_TANK_TEXTURE_NAME{ "textures/at_spg.png" };
inline static const std::string SPG_TANK_TEXTURE_NAME{ "textures/spg.png" };
inline static const std::string LIGHT_TANK_TEXTURE_NAME{ "textures/light.png" };
inline static const std::string HEAVY_TANK_TEXTURE_NAME{ "textures/heavy.png" };
inline static const std::string MEDIUM_TANK_TEXTURE_NAME{ "textures/medium.png" };

inline static const std::string AT_SPG_HEALTH_BAR_ROSE_TEXTURE_NAME{ "textures/at_spg_health_bar_rose.png" };
inline static const std::string SPG_HEALTH_BAR_ROSE_TEXTURE_NAME{ "textures/spg_health_bar_rose.png" };
inline static const std::string LIGHT_HEALTH_BAR_ROSE_TEXTURE_NAME{ "textures/light_health_bar_rose.png" };
inline static const std::string HEAVY_HEALTH_BAR_ROSE_TEXTURE_NAME{ "textures/heavy_health_bar_rose.png" };
inline static const std::string MEDIUM_HEALTH_BAR_ROSE_TEXTURE_NAME{ "textures/medium_health_bar_rose.png" };

inline static const std::string AT_SPG_HEALTH_BAR_ORANGE_TEXTURE_NAME{ "textures/at_spg_health_bar_orange.png" };
inline static const std::string SPG_HEALTH_BAR_ORANGE_TEXTURE_NAME{ "textures/spg_health_bar_orange.png" };
inline static const std::string LIGHT_HEALTH_BAR_ORANGE_TEXTURE_NAME{ "textures/light_health_bar_orange.png" };
inline static const std::string HEAVY_HEALTH_BAR_ORANGE_TEXTURE_NAME{ "textures/heavy_health_bar_orange.png" };
inline static const std::string MEDIUM_HEALTH_BAR_ORANGE_TEXTURE_NAME{ "textures/medium_health_bar_orange.png" };

inline static const std::string AT_SPG_HEALTH_BAR_BLUE_TEXTURE_NAME{ "textures/at_spg_health_bar_blue.png" };
inline static const std::string SPG_HEALTH_BAR_BLUE_TEXTURE_NAME{ "textures/spg_health_bar_blue.png" };
inline static const std::string LIGHT_HEALTH_BAR_BLUE_TEXTURE_NAME{ "textures/light_health_bar_blue.png" };
inline static const std::string HEAVY_HEALTH_BAR_BLUE_TEXTURE_NAME{ "textures/heavy_health_bar_blue.png" };
inline static const std::string MEDIUM_HEALTH_BAR_BLUE_TEXTURE_NAME{ "textures/medium_health_bar_blue.png" };

inline static const std::string FRIEND_HP_TEXTURE_NAME{ "textures/friend_hp.png" };
inline static const std::string ENEMY_HP_TEXTURE_NAME{ "textures/enemy_hp.png" };
inline static const std::string NEUTRAL_HP_TEXTURE_NAME{ "textures/neutral_hp.png" };

inline static const std::string HARD_REPAIR_TEXTURE_NAME("textures/hard_repair.png");
inline static const std::string LIGHT_REPAIR_TEXTURE_NAME("textures/light_repair.png");
inline static const std::string CATAPULT_TEXTURE_NAME("textures/catapult.png");
