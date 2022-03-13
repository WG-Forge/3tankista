#pragma once

#include "components/capture_points_component.h"
#include "components/kill_points_component.h"
#include "components/player_id_component.h"
#include "components/transform_component.h"
#include "components/ttc_component.h"
#include "components/turn_component.h"
#include "components/vehicle_id_component.h"
#include "ecs.h"
#include "entities/map/map.h"
#include "game/game_events.h"

class WinSystem : public ecs::System<WinSystem>, public ecs::event::IEventListener
{
public:
    WinSystem();
    ~WinSystem() override;

    void        OnTankDestroyedEvent(const TankDestroyedEvent* event);
    void        OnMoveResponseEvent(const MoveResponseEvent* event);
    void        OnUpdateCapturePointsEvent(const UpdateCapturePointsEvent* event);
    static void UpdateCapturePoints();
    static std::vector<std::pair<uint64_t, std::pair<int, int>>> GetWinPoints();
    static int GetMaxKillPoints(std::vector<std::pair<uint64_t, std::pair<int, int>>> map);

private:
    void RegisterEventCallbacks();
    void UnregisterEventCallbacks();
};
