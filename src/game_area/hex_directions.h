#pragma once

#include "utility/matrix.hpp"

class HexDirections
{
public:
    HexDirections();
    virtual ~HexDirections() =default;
    const auto  Size() const { return directions.size(); }
    const auto& operator[](int index) const { return directions[index]; }

protected:
    void SetDirections(std::vector<Vector2i>& directions)
    {
        this->directions = std::move(directions);
    }
    auto& GetDirections() { return this->directions; }

    const auto& GetDirections() const { return this->directions; }

private:
    std::vector<Vector2i> directions;
};
