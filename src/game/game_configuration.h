#pragma once

#include "utility/matrix.hpp"

static constexpr float DELTA_TIME_STEP{ 1.0f / 60.0f };

static constexpr unsigned int GAME_WINDOW_WIDTH{ 1920 };

static constexpr unsigned int GAME_WINDOW_HEIGHT{ 1080 };

static constexpr bool GAME_WINDOW_FULLSCREEN{ false };

static constexpr std::size_t HEX_SIZE{ std::size_t(32 * 1.75) };

inline static const std::size_t LONG_DIAGONAL =
    HEX_SIZE * std::sqrt(3) / 2.0; // 1/2 from short hex diagonal
inline static const std::size_t SHORT_DIAGONAL =
    HEX_SIZE / 2.0; // 1/4 from long hex diagonal

inline static const Matrix2f GRID_BASIS{ { (float)SHORT_DIAGONAL, 0 },
                                         { 0, (float)LONG_DIAGONAL } };
inline static const Matrix2f HEX_BASIS{
    { (GRID_BASIS.getCol(0) * 3 + GRID_BASIS.getCol(1)).x(),
      (GRID_BASIS.getCol(1) * 2).x() },
    { (GRID_BASIS.getCol(0) * 3 + GRID_BASIS.getCol(1)).y(),
      (GRID_BASIS.getCol(1) * 2).y() }
};
