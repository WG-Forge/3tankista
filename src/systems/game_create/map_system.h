#pragma once

#include "systems/gameplay_system.h"
#include "components/hex_map_component.h"
#include "components/turn_component.h"
#include "ecs.h"
#include "entities/map/map.h"
#include "game/game_events.h"
#include "game/models/models.h"
#include <iostream>

class MapSystem : public ecs::System<MapSystem>, public ecs::event::IEventListener
{
public:
    MapSystem();
    ~MapSystem() override;

    void OnMapResponse(const MapResponseEvent* event);

private:
    void RegisterEventCallbacks();
    void UnregisterEventCallbacks();
};
