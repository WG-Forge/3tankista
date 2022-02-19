#pragma once

#include "ecs.h"
#include "game/game_events.h"

class WinSystem : public ecs::System<WinSystem>, public ecs::event::IEventListener
{
public:
    WinSystem();
    ~WinSystem() override;

    void OnTankDestroyedEvent(const TankDestroyedEvent* event);
    void OnUpdateCapturePointsEvent(const UpdateCapturePointsEvent* event);

private:
    void RegisterEventCallbacks();
    void UnregisterEventCallbacks();
};
