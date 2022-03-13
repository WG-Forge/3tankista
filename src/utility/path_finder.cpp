#include "path_finder.h"
#include <queue>

const std::vector<Vector2i> PathFinder::HEX_DIRECTIONS = { { 1, 0 },  { 1, -1 }, { 0, -1 },
                                                           { -1, 0 }, { -1, 1 }, { 0, 1 } };

void PathFinder::AStar()
{
    this->lastDirections.assign((area->GetSize() << 1) | 1, std::vector<signed char>((area->GetSize() << 1) | 1, -1));
    this->distance.assign((area->GetSize() << 1) | 1, std::vector<int>((area->GetSize() << 1) | 1, NO_PATH));

    std::priority_queue<std::pair<Vector2i, int>,
                        std::vector<std::pair<Vector2i, int>>,
                        std::function<bool(std::pair<Vector2i, int>&, std::pair<Vector2i, int>&)>>
        queue([](std::pair<Vector2i, int>& lhs, std::pair<Vector2i, int>& rhs) { return lhs.second > rhs.second; });
    queue.push(std::make_pair(from, 0));
    this->distance[from.x()][from.y()] = 0;
    while (!queue.empty())
    {
        auto position = queue.top().first;
        queue.pop();
        if (position == to)
        {
            break;
        }
        for (int i = 0; i < HEX_DIRECTIONS.size(); i++)
        {
            auto destination = position + HEX_DIRECTIONS[i];
            if (!MapUtility::IsValid(destination, area->GetSize()) || !IS_REACHABLE(area->GetCell(destination)))
                continue;
            auto newDistance = distance[position.x()][position.y()] + 1;
            if (this->distance[destination.x()][destination.y()] == NO_PATH ||
                newDistance < this->distance[destination.x()][destination.y()])
            {
                this->distance[destination.x()][destination.y()] = newDistance;
                auto priority = newDistance + MapUtility::GetDistance(destination, to);
                queue.push(std::make_pair(destination, priority));
                this->lastDirections[destination.x()][destination.y()] = i;
            }
        }
    }
}
int PathFinder::GetDistance()
{
    return distance[to.x()][to.y()];
}

std::vector<Vector3i> PathFinder::GetShortestPath()
{
    Vector2i              now = to;
    std::vector<Vector3i> result;
    if (distance[now.x()][now.y()] == NO_PATH)
        return result;
    while (!(now == from))
    {
        result.push_back(MapUtility::Hex2Cube(MapUtility::Shift(now, -(area->GetSize()))));
        now -= HEX_DIRECTIONS[lastDirections[now.x()][now.y()]];
    }
    std::reverse(result.begin(), result.end());
    return result;
}

bool PathFinder::Find(const Vector3i& from, const Vector3i& to)
{
    this->from = MapUtility::Shift(MapUtility::Cube2Hex(from), area->GetSize());
    this->to   = MapUtility::Shift(MapUtility::Cube2Hex(to), area->GetSize());
    AStar();
    return this->distance[this->to.x()][this->to.y()] != NO_PATH;
}
