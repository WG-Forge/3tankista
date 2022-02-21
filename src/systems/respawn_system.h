#pragma once

#include "ecs.h"
#include "game/game_events.h"

class RespawnSystem : public ecs::System<RespawnSystem>, public ecs::event::IEventListener
{
public:
    RespawnSystem();
    ~RespawnSystem();

    void OnTankDestroyedEvent(const TankDestroyedEvent* event);

private:
    void RegisterEventCallbacks();
    void UnregisterEventCallbacks();
};
