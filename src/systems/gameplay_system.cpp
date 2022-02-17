#include "gameplay_system.h"
#include <queue>

const std::vector<Vector2i> GameplaySystem::HEX_DIRECTIONS = {
    { 1, 0 }, { 1, -1 }, { 0, -1 }, { -1, 0 }, { -1, 1 }, { 0, 1 }
};

GameplaySystem::GameplaySystem()
{
    RegisterEventCallbacks();
}

GameplaySystem::~GameplaySystem()
{
    UnregisterEventCallbacks();
}

Vector2i GameplaySystem::Cube2Hex(const Vector3i& point)
{
    return Vector2i(point.x(), point.z());
}

Vector3i GameplaySystem::Hex2Cube(const Vector2i& point)
{
    return Vector3i(point.x(), -point.x() - point.y(), point.y());
}

int GameplaySystem::GetDistance(const Vector3i& first, const Vector3i& second)
{
    return (abs(first.x() - second.x()) + abs(first.y() - second.y()) +
            abs(first.z() - second.z())) /
           2;
}

int GameplaySystem::GetDistance(const Vector2i& first, const Vector2i& second)
{
    return GetDistance(Hex2Cube(first), Hex2Cube(second));
}

Vector3i GameplaySystem::Shift(const Vector3i& position, int value)
{
    return Vector3i(
        position.x() + value, position.y() + value, position.z() + value);
}

Vector2i GameplaySystem::Shift(const Vector2i& position, int value)
{
    return Vector2i(position.x() + value, position.y() + value);
}

bool GameplaySystem::IsValid(const Vector2i& point, const int size)
{
    return GetDistance(point, Vector2i(size, size)) <= size;
}

bool GameplaySystem::IsValid(const Vector3i& point, const int size)
{
    return IsValid(Shift(Cube2Hex(point), size), size);
}

void GameplaySystem::SetHexMapComponentCell(HexMapComponent* component,
                                            const Vector3i&  position,
                                            const CellState& state)
{
    component->SetCell(Shift(Cube2Hex(position), component->GetSize()), state);
}

CellState GameplaySystem::GetHexMapComponentCell(HexMapComponent* component,
                                                 const Vector3i&  position)
{
    return component->GetCell(Shift(Cube2Hex(position), component->GetSize()));
}

void GameplaySystem::PathFinder::Bfs(const Vector2i& from)
{
    this->used.assign((area->GetSize() << 1) | 1,
                      std::vector<bool>((area->GetSize() << 1) | 1, false));
    this->lastDirections.assign(
        (area->GetSize() << 1) | 1,
        std::vector<signed char>((area->GetSize() << 1) | 1, -1));
    this->distance.assign(
        (area->GetSize() << 1) | 1,
        std::vector<int>((area->GetSize() << 1) | 1, NO_PATH));
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
            if (!GameplaySystem::IsValid(destination, area->GetSize()) ||
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

int GameplaySystem::PathFinder::GetDistance(const Vector3i& point)
{
    auto newPoint =
        GameplaySystem::Shift(GameplaySystem::Cube2Hex(point), area->GetSize());
    return distance[newPoint.x()][newPoint.y()];
}

std::vector<Vector3i> GameplaySystem::PathFinder::GetShortestPath(
    const Vector3i& point)
{
    Vector2i now =
        GameplaySystem::Shift(GameplaySystem::Cube2Hex(point), area->GetSize());
    std::vector<Vector3i> result;
    if (distance[now.x()][now.y()] == NO_PATH)
        return result;
    while (!(now == startPoint))
    {
        result.push_back(GameplaySystem::Hex2Cube(
            GameplaySystem::Shift(now, -(area->GetSize()))));
        now -= HEX_DIRECTIONS[lastDirections[now.x()][now.y()]];
    }
    std::reverse(result.begin(), result.end());
    return result;
}

void GameplaySystem::RegisterEventCallbacks() {}

void GameplaySystem::UnregisterEventCallbacks() {}
