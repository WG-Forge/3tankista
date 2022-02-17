#pragma once

#include "game/game_events.h"
#include "game/models/models.h"
#include "ecs.h"

class MapSystem : public ecs::System<MapSystem>,
                   public ecs::event::IEventListener
{
public:
    MapSystem();
    ~MapSystem() override;

    void OnMapResponce(const MapResponceEvent* event);

private:
    void RegisterEventCallbacks();
    void UnregisterEventCallbacks();
};
