#pragma once

#include "game_area.h"
#include "hex_directions.h"

#define NOPATH -1

class PathFinder
{
public:
    PathFinder();
    PathFinder(std::shared_ptr<GameArea>  area);
    virtual ~PathFinder() {}

    int                   GetDistance(const Vector3i& point);
    std::vector<Vector3i> GetShortestPath(const Vector3i& point);

    auto& GetGameArea() { return this->area; }

protected:
    HexDirections hexDirections;
    void          Bfs(const Vector2i& from);

public:
    void SetStartPoint(const Vector3i& point)
    {
        startPoint =
            GameArea::Shift(GameArea::Cube2Hex(point), area->GetSize());
        Bfs(startPoint);
    }
    auto GetStartPoint()
    {
        return GameArea::Hex2Cube(
            GameArea::Shift(startPoint, -area->GetSize()));
    }

private:
    std::shared_ptr<GameArea>             area;
    Vector2i                              startPoint;
    std::vector<std::vector<bool>>        used;
    std::vector<std::vector<signed char>> lastDirections;
    std::vector<std::vector<int>>         distance;
};
