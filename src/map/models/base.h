#pragma once

#include "nlohmann/json.hpp"
#include "utility/matrix.hpp"

struct Base
{
public:
    void SetHexes(std::vector<Vector3i>& hexes)
    {
        this->hexes = std::move(hexes);
    }
    auto&       GetHexes() { return this->hexes; }
    const auto& GetHexes() const { return this->hexes; }

private:
    std::vector<Vector3i> hexes;
};
