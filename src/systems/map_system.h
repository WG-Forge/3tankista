#pragma once

#include "ecs.h"
#include "game/game_events.h"
#include "game/models/models.h"

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
