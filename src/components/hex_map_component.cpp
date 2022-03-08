#include "hex_map_component.h"

HexMapComponent::HexMapComponent(int size)
    : size(size)
    , map((size << 1) | 1, std::vector<int32_t>((size << 1) | 1, 0))
{
}

int32_t HexMapComponent::GetCell(const Vector2i& position) const
{
    return map[position.x()][position.y()];
}

void HexMapComponent::ClearMap()
{
    map.assign((size << 1) | 1, std::vector<int32_t>((size << 1) | 1, 0));
}

void HexMapComponent::SetCell(const Vector2i& position, const int32_t state)
{
    map[position.x()][position.y()] = state;
}

void HexMapComponent::AddToCell(const Vector2i& position, const CellState& state)
{
    map[position.x()][position.y()] |= (int32_t)state;
}

void HexMapComponent::RemoveFromCell(const Vector2i& position, const CellState& state)
{
    map[position.x()][position.y()] &= ~((int32_t)state);
}
