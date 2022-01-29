#include "hexdirections.h"

HexDirections::HexDirections()
{
    directions.emplace_back(1, 0);
    directions.emplace_back(1, -1);
    directions.emplace_back(0, -1);
    directions.emplace_back(-1, 0);
    directions.emplace_back(-1, 1);
    directions.emplace_back(0, 1);
}