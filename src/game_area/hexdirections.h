#ifndef SERVER_HEXDIRECTIONS_H
#define SERVER_HEXDIRECTIONS_H

#include "matrix.hpp"

class HexDirections
{
public:
    HexDirections();
    virtual ~HexDirections() =default;
    const auto  Size() const { return directions.size(); }
    const auto& operator[](int index) const { return directions[index]; }

protected:
    void SetDirections(const std::vector<Vector2i>& directions)
    {
        this->directions = directions;
    }
    auto& GetDirections() { return this->directions; }

    const auto& GetDirections() const { return this->directions; }

private:
    std::vector<Vector2i> directions;
};

#endif // SERVER_HEXDIRECTIONS_H
