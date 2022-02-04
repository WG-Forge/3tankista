#include "path_finder.h"
#include <queue>
#include <utility>

PathFinder::PathFinder()
    : area()
    , startPoint()
    , used()
    , lastDirections()
    , distance()
    , hexDirections()
{
}

PathFinder::PathFinder(std::shared_ptr<GameArea> area)
    : area(std::move(area))
    , startPoint()
    , used()
    , lastDirections()
    , distance()
    , hexDirections()
{
}

void PathFinder::Bfs(const Vector2i& from)
{
    this->used.assign((area->GetSize() << 1) | 1,
                      std::vector<bool>((area->GetSize() << 1) | 1, false));
    this->lastDirections.assign(
        (area->GetSize() << 1) | 1,
        std::vector<signed char>((area->GetSize() << 1) | 1, -1));
    this->distance.assign((area->GetSize() << 1) | 1,
                          std::vector<int>((area->GetSize() << 1) | 1, NOPATH));
    std::queue<Vector2i> q;
    q.push(from);
    this->used[from.x()][from.y()]     = true;
    this->distance[from.x()][from.y()] = 0;
    while (!q.empty())
    {
        auto now = q.front();
        q.pop();
        for (int i = 0; i < hexDirections.Size(); i++)
        {
            auto destination = now + hexDirections[i];
            if (!area->IsValid(destination) ||
                area->GetCell(destination) != CellState::EMPTY)
                continue;
            if (!this->used[destination.x()][destination.y()])
            {
                this->used[destination.x()][destination.y()]           = true;
                this->lastDirections[destination.x()][destination.y()] = i;
                this->distance[destination.x()][destination.y()] =
                    distance[now.x()][now.y()] + 1;
                q.push(destination);
            }
        }
    }
}

int PathFinder::GetDistance(const Vector3i& point)
{
    auto newPoint = GameArea::Shift(GameArea::Cube2Hex(point), area->GetSize());
    return distance[newPoint.x()][newPoint.y()];
}

std::vector<Vector3i> PathFinder::GetShortestPath(const Vector3i& point)
{
    Vector2i now = GameArea::Shift(GameArea::Cube2Hex(point), area->GetSize());
    std::vector<Vector3i> result;
    if (distance[now.x()][now.y()] == NOPATH)
        return result;
    while (!(now == startPoint))
    {
        result.push_back(
            GameArea::Hex2Cube(GameArea::Shift(now, -(area->GetSize()))));
        now -= hexDirections[lastDirections[now.x()][now.y()]];
    }
    std::reverse(result.begin(), result.end());
    return result;
}
