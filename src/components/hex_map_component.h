#pragma once

#include "ecs.h"
#include "enums/cell_state.h"
#include "utility/matrix.hpp"

class HexMapComponent : public ecs::Component<HexMapComponent>
{
public:
    explicit HexMapComponent(int size);
    ~HexMapComponent() override = default;

    void    SetCell(const Vector2i& position, int32_t state);
    void    AddToCell(const Vector2i& position, const CellState& state);
    void    RemoveFromCell(const Vector2i& position, const CellState& state);
    int32_t GetCell(const Vector2i& position) const;

    void ClearMap();

    void SetSize(const int size)
    {
        this->size = size;
        ClearMap();
    }
    auto GetSize() const { return this->size; }

protected:
    void        SetMap(std::vector<std::vector<int32_t>>& map) { this->map = std::move(map); }
    auto&       GetMap() { return this->map; }
    const auto& GetMap() const { return this->map; }

private:
    int                                size;
    std::vector<std::vector<int32_t>>  map;
};
