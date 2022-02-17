#include "hex_map_component.h"

HexMapComponent::HexMapComponent(int size)
    : size(size)
    , map((size << 1) | 1,
          std::vector<CellState>((size << 1) | 1, CellState::EMPTY))
{
}

void HexMapComponent::SetCell(const Vector2i& position, const CellState& state)
{
    map[position.x()][position.y()] = state;
}

CellState HexMapComponent::GetCell(const Vector2i& position) const
{
    return map[position.x()][position.y()];
}

void HexMapComponent::ClearMap()
{
    map.assign((size << 1) | 1,
               std::vector<CellState>((size << 1) | 1, CellState::EMPTY));
}