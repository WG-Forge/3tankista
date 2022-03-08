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

    int                   GetDistance(const Vector3i& point);
    std::vector<Vector3i> GetShortestPath(const Vector3i& point);

    auto& GetGameArea() { return this->area; }
    void  Bfs(const Vector2i& from);

public:
    void SetHexMapComponent(HexMapComponent* component) { area = component; }
    auto GetHexMapComponent() { return area; }

    void SetStartPoint(const Vector3i& point)
    {
        startPoint = MapUtility::Shift(MapUtility::Cube2Hex(point), area->GetSize());
        Bfs(startPoint);
    }
    auto GetStartPoint() { return MapUtility::Hex2Cube(MapUtility::Shift(startPoint, -area->GetSize())); }

private:
    HexMapComponent*                      area = nullptr;
    Vector2i                              startPoint;
    std::vector<std::vector<bool>>        used;
    std::vector<std::vector<signed char>> lastDirections;
    std::vector<std::vector<int>>         distance;
};