#ifndef SERVER_PATHFINDER_H
#define SERVER_PATHFINDER_H

#include "gamearea.h"
#include "hexdirections.h"

class PathFinder
{
public:
    PathFinder(const std::shared_ptr<GameArea>& area);
    virtual ~PathFinder() {}

    int                   GetDistance(const Vector3i& point);
    std::vector<Vector3i> GetShortestPath(const Vector3i& point);

protected:
    inline static const HexDirections HEX_DIRECTIONS = HexDirections();
    void                              Bfs(const Vector2i& from);

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

#endif // SERVER_PATHFINDER_H
