#pragma once

#define IS_REACHABLE(cell) (!((cell) & 0xf))
#define CELL_CONTAINS(a, b) (!!((int32_t)(a) & (int32_t)(b)))

enum class CellState
{
    EMPTY        = 0,
    ENEMY        = 1,
    FRIEND       = 2,
    ENEMY_SPAWN  = 4,
    OBSTACLE     = 8,
    BASE         = 16,
    HARD_REPAIR  = 32,
    LIGHT_REPAIR = 64
};
