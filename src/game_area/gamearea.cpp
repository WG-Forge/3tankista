#include "gamearea.h"

GameArea::GameArea(const Map& map)
    : size(map.GetSize())
    , map((size << 1) | 1,
          std::vector<CellState>((size << 1) | 1, CellState::EMPTY))
{
}

Vector2i GameArea::Cube2Hex(const Vector3i& point)
{
    return Vector2i(point.x(), point.z());
}

Vector3i GameArea::Hex2Cube(const Vector2i& point)
{
    return Vector3i(point.x(), -point.x() - point.y(), point.y());
}

int GameArea::GetDistance(const Vector3i& first, const Vector3i& second)
{
    return (abs(first.x() - second.x()) + abs(first.y() - second.y()) +
            abs(first.z() - second.z())) /
           2;
}

int GameArea::GetDistance(const Vector2i& first, const Vector2i& second)
{
    return GetDistance(Hex2Cube(first), Hex2Cube(second));
}

bool GameArea::IsValid(const Vector2i& point) const
{
    return GetDistance(point, Vector2i(size, size)) <= size;
}

bool GameArea::IsValid(const Vector3i& point) const
{
    return IsValid(Shift(Cube2Hex(point), size));
}

Vector3i GameArea::Shift(const Vector3i& position, int value)
{
    return Vector3i(
        position.x() + value, position.y() + value, position.z() + value);
}

Vector2i GameArea::Shift(const Vector2i& position, int value)
{
    return Vector2i(position.x() + value, position.y() + value);
}

void GameArea::SetCell(const Vector3i& position, const CellState& state)
{
    SetCell(Shift(Cube2Hex(position), size), state);
}

void GameArea::SetCell(const Vector2i& position, const CellState& state)
{
    map[position.x()][position.y()] = state;
}

CellState GameArea::GetCell(const Vector3i& position) const
{
    return GetCell(Shift(Cube2Hex(position), size));
}

CellState GameArea::GetCell(const Vector2i& position) const
{
    return map[position.x()][position.y()];
}

void GameArea::ClearMap()
{
    map.assign((size << 1) | 1,
               std::vector<CellState>((size << 1) | 1, CellState::EMPTY));
}
