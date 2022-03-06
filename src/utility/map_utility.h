#pragma once

#include "components/hex_map_component.h"
#include "matrix.hpp"

class MapUtility
{
public:
    /**
     * Convert point in cubic coordinates to hex.
     * @param point - point to convert
     * @return point in hex coordinates.
     */
    static inline Vector2i Cube2Hex(const Vector3i& point) { return Vector2i(point.x(), point.z()); }

    /**
     * Convert point in hex coordinates to cubic.
     * @param point  - point to convert
     * @return point in cubic coordinates.
     */
    static inline Vector3i Hex2Cube(const Vector2i& point)
    {
        return Vector3i(point.x(), -point.x() - point.y(), point.y());
    }

    /**
     * Getting the distance on a hexagonal grid without taking into account
     * obstacles.
     * @param first - first point in cubic coords
     * @param second - second point in cubic coords
     * @return distance between points.
     */
    static inline int GetDistance(const Vector3i& first, const Vector3i& second)
    {
        return (abs(first.x() - second.x()) + abs(first.y() - second.y()) + abs(first.z() - second.z())) / 2;
    }

    /**
     * Getting the distance on a hexagonal grid without taking into account
     * obstacles.
     * @param first - first point in hex coords
     * @param second - second point in hex coords
     * @return distance between points.
     */
    static inline int GetDistance(const Vector2i& first, const Vector2i& second)
    {
        return GetDistance(Hex2Cube(first), Hex2Cube(second));
    }

    static inline Vector3i Shift(const Vector3i& position, int value)
    {
        return Vector3i(position.x() + value, position.y() + value, position.z() + value);
    }

    static inline Vector2i Shift(const Vector2i& position, int value)
    {
        return Vector2i(position.x() + value, position.y() + value);
    }

    static inline void SetHexMapComponentCell(HexMapComponent* component,
                                              const Vector3i&  position,
                                              const CellState& state)
    {

        component->SetCell(Shift(Cube2Hex(position), component->GetSize()), state);
    }
    static inline CellState GetHexMapComponentCell(HexMapComponent* component, const Vector3i& position)
    {
        return component->GetCell(Shift(Cube2Hex(position), component->GetSize()));
    }

    /**
     * Checks whether a point in cubic coordinates belongs to a hexagonal grid.
     * @param point - point to check
     * @param size - size of map
     * @return result of check.
     */
    static inline bool IsValid(const Vector3i& point, int size) { return IsValid(Shift(Cube2Hex(point), size), size); }

    /**
     * Checks whether a point in hex shifted coordinates belongs to a hexagonal
     * grid.
     * @param point - point to check
     * @param size - size of map
     * @return result of check.
     */
    static inline bool IsValid(const Vector2i& point, int size)
    {
        return GetDistance(point, Vector2i(size, size)) <= size;
    }
};
