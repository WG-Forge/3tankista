#ifndef SERVER_AREA_H
#define SERVER_AREA_H

#include "map.h"
#include "matrix.hpp"

enum class CellState
{
    EMPTY,
    ENEMY,
    FRIEND
};

class GameArea
{
public:
    GameArea(const Map& map);
    virtual ~GameArea() {}

    /**
     * Convert point in cubic coordinates to hex.
     * @param point - point to convert
     * @return point in hex coordinates.
     */
    static inline Vector2i Cube2Hex(const Vector3i& point);

    /**
     * Convert point in hex coordinates to cubic.
     * @param point  - point to convert
     * @return point in cubic coordinates.
     */
    static inline Vector3i Hex2Cube(const Vector2i& point);

    /**
     * Getting the distance on a hexagonal grid without taking into account
     * obstacles.
     * @param first - first point in cubic coords
     * @param second - second point in cubic coords
     * @return distance between points.
     */
    static inline int GetDistance(const Vector3i& first,
                                  const Vector3i& second);

    /**
     * Getting the distance on a hexagonal grid without taking into account
     * obstacles.
     * @param first - first point in hex coords
     * @param second - second point in hex coords
     * @return distance between points.
     */
    static inline int GetDistance(const Vector2i& first,
                                  const Vector2i& second);

    static inline Vector3i Shift(const Vector3i& position, int value);
    static inline Vector2i Shift(const Vector2i& position, int value);

    void SetCell(const Vector3i& position, const CellState& state);
    void SetCell(const Vector2i& position, const CellState& state);

    CellState GetCell(const Vector3i& position) const;
    CellState GetCell(const Vector2i& position) const;

    /**
     * Checks whether a point in cubic coordinates belongs to a hexagonal grid.
     * @param point - point to check
     * @return result of check.
     */
    bool IsValid(const Vector3i& point) const;

    /**
     * Checks whether a point in hex shifted coordinates belongs to a hexagonal
     * grid.
     * @param point - point to check
     * @return result of check.
     */
    bool IsValid(const Vector2i& point) const;

    void ClearMap();

protected:
    void SetSize(const int& size) { this->size = size; }

public:
    auto&       GetSize() { return this->size; }
    const auto& GetSize() const { return this->size; }

protected:
    void SetMap(const std::vector<std::vector<CellState>>& map)
    {
        this->map = map;
    }
    auto&       GetMap() { return this->map; }
    const auto& GetMap() const { return this->map; }

private:
    int                                 size;
    std::vector<std::vector<CellState>> map;
};

#endif // SERVER_AREA_H
