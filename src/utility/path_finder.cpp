#include "path_finder.h"
#include <queue>

const std::vector<Vector2i> PathFinder::HEX_DIRECTIONS = { { 1, 0 },  { 1, -1 }, { 0, -1 },
                                                           { -1, 0 }, { -1, 1 }, { 0, 1 } };

void PathFinder::Bfs(const Vector2i& from)
{
    this->used.assign((area->GetSize() << 1) | 1, std::vector<bool>((area->GetSize() << 1) | 1, false));
    this->lastDirections.assign((area->GetSize() << 1) | 1, std::vector<signed char>((area->GetSize() << 1) | 1, -1));
    this->distance.assign((area->GetSize() << 1) | 1, std::vector<int>((area->GetSize() << 1) | 1, NO_PATH));
    std::queue<Vector2i> q;
    q.push(from);
    this->used[from.x()][from.y()]     = true;
    this->distance[from.x()][from.y()] = 0;
    while (!q.empty())
    {
        auto now = q.front();
        q.pop();
        for (int i = 0; i < HEX_DIRECTIONS.size(); i++)
        {
            auto destination = now + HEX_DIRECTIONS[i];
            if (!MapUtility::IsValid(destination, area->GetSize()) || !IS_REACHABLE(area->GetCell(destination)))
                continue;
            if (!this->used[destination.x()][destination.y()])
            {
                this->used[destination.x()][destination.y()]           = true;
                this->lastDirections[destination.x()][destination.y()] = i;
                this->distance[destination.x()][destination.y()]       = distance[now.x()][now.y()] + 1;
                q.push(destination);
            }
        }
    }
}

int PathFinder::GetDistance(const Vector3i& point)
{
    auto newPoint = MapUtility::Shift(MapUtility::Cube2Hex(point), area->GetSize());
    return distance[newPoint.x()][newPoint.y()];
}

std::vector<Vector3i> PathFinder::GetShortestPath(const Vector3i& point)
{
    Vector2i              now = MapUtility::Shift(MapUtility::Cube2Hex(point), area->GetSize());
    std::vector<Vector3i> result;
    if (distance[now.x()][now.y()] == NO_PATH)
        return result;
    while (!(now == startPoint))
    {
        result.push_back(MapUtility::Hex2Cube(MapUtility::Shift(now, -(area->GetSize()))));
        now -= HEX_DIRECTIONS[lastDirections[now.x()][now.y()]];
    }
    std::reverse(result.begin(), result.end());
    return result;
}