#pragma once

#include "map_utility.h"
#include "matrix.hpp"
#include "systems/gameplay_system.h"

class PathFinder
{
public:
    static const std::vector<Vector2i> HEX_DIRECTIONS;
    static constexpr int               NO_PATH = -1;

    PathFinder()          = default;
    virtual ~PathFinder() = default;

    int                   GetDistance();
    std::vector<Vector3i> GetShortestPath();

    bool Find(const Vector3i& from, const Vector3i& to);

    void SetHexMapComponent(HexMapComponent* component) { area = component; }
    auto GetHexMapComponent() { return area; }

protected:
    void AStar();

private:
    Vector2i                              from, to;
    HexMapComponent*                      area = nullptr;
    std::vector<std::vector<bool>>        used;
    std::vector<std::vector<signed char>> lastDirections;
    std::vector<std::vector<int>>         distance;
};