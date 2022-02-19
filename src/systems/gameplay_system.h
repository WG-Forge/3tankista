#pragma once

#include "components/hex_map_component.h"
#include "ecs.h"
#include "entities/tank.h"
#include "game/game_events.h"
#include "utility/matrix.hpp"

class GameplaySystem : public ecs::System<GameplaySystem>, public ecs::event::IEventListener
{
public:
    GameplaySystem();
    ~GameplaySystem() override;

    void OnPlayEvent(const PlayEvent* event);

private:
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
    static inline int GetDistance(const Vector3i& first, const Vector3i& second);

    /**
     * Getting the distance on a hexagonal grid without taking into account
     * obstacles.
     * @param first - first point in hex coords
     * @param second - second point in hex coords
     * @return distance between points.
     */
    static inline int GetDistance(const Vector2i& first, const Vector2i& second);

    static inline Vector3i Shift(const Vector3i& position, int value);
    static inline Vector2i Shift(const Vector2i& position, int value);

    static inline void      SetHexMapComponentCell(HexMapComponent* component,
                                                   const Vector3i&  position,
                                                   const CellState& state);
    static inline CellState GetHexMapComponentCell(HexMapComponent* component, const Vector3i& position);

    /**
     * Checks whether a point in cubic coordinates belongs to a hexagonal grid.
     * @param point - point to check
     * @param size - size of map
     * @return result of check.
     */
    static inline bool IsValid(const Vector3i& point, int size);

    /**
     * Checks whether a point in hex shifted coordinates belongs to a hexagonal
     * grid.
     * @param point - point to check
     * @param size - size of map
     * @return result of check.
     */
    static inline bool IsValid(const Vector2i& point, int size);

    class PathFinder
    {
    public:
        static const std::vector<Vector2i> HEX_DIRECTIONS;
        static constexpr int               NO_PATH = -1;

        PathFinder()          = default;
        virtual ~PathFinder() = default;

        int                   GetDistance(const Vector3i& point);
        std::vector<Vector3i> GetShortestPath(const Vector3i& point);

        auto& GetGameArea() { return this->area; }
        void  Bfs(const Vector2i& from);

    public:
        void SetHexMapComponent(HexMapComponent* component) { area = component; }
        auto GetHexMapComponent() { return area; }

        void SetStartPoint(const Vector3i& point)
        {
            startPoint = GameplaySystem::Shift(GameplaySystem::Cube2Hex(point), area->GetSize());
            Bfs(startPoint);
        }
        auto GetStartPoint() { return GameplaySystem::Hex2Cube(GameplaySystem::Shift(startPoint, -area->GetSize())); }

    private:
        HexMapComponent*                      area = nullptr;
        Vector2i                              startPoint;
        std::vector<std::vector<bool>>        used;
        std::vector<std::vector<signed char>> lastDirections;
        std::vector<std::vector<int>>         distance;
    };

    bool CheckNeutrality(Tank* playerTank, Tank* enemyTank);
    bool CanShoot(Tank* playerTank, Tank* enemyTank);

private:
    void RegisterEventCallbacks();
    void UnregisterEventCallbacks();

private:
    PathFinder pathFinder;
};
