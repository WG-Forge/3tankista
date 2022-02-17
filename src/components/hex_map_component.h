#pragma once

#include "ecs.h"
#include "utility/matrix.hpp"

enum class CellState
{
    EMPTY,
    ENEMY,
    FRIEND,
    OBSTACLE
};

class HexMapComponent : public ecs::Component<HexMapComponent>
{
public:
    explicit HexMapComponent(int size);
    ~HexMapComponent() override = default;

    void      SetCell(const Vector2i& position, const CellState& state);
    CellState GetCell(const Vector2i& position) const;

    void ClearMap();

    void SetSize(const int size)
    {
        this->size = size;
        ClearMap();
    }
    auto GetSize() const { return this->size; }

protected:
    void SetMap(std::vector<std::vector<CellState>>& map)
    {
        this->map = std::move(map);
    }
    auto&       GetMap() { return this->map; }
    const auto& GetMap() const { return this->map; }

private:
    int                                 size;
    std::vector<std::vector<CellState>> map;
};
