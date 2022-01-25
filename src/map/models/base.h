#ifndef BASE_H
#define BASE_H

#include "matrix.hpp"

#include "nlohmann/json.hpp"

struct Base
{
public:
    void  SetHexes(const std::vector<Vector3d>& hexes) { this->hexes = hexes; }
    auto& GetHexes() { return this->hexes; }
    const auto& GetHexes() const { return this->hexes; }

private:
    std::vector<Vector3d> hexes;
};

#endif // BASE_H
