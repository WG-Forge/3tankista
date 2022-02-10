#pragma once

#include "game/game_events.h"

#include "ecs.h"

class HealthSystem : public ecs::System<HealthSystem>,
                     public ecs::event::IEventListener
{
public:
    HealthSystem();
    ~HealthSystem() override;

    void OnShootResponce(const ShootResponceEvent* event);

private:
    void RegisterEventCallbacks();
    void UnregisterEventCallbacks();
};
