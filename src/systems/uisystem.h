#pragma once

#include "game/game_events.h"

#include "ecs.h"

class UiSystem : public ecs::System<UiSystem>, public ecs::event::IEventListener
{
public:
    UiSystem();
    virtual ~UiSystem() override;

public:
    void OnHealthChanged(const HealthChanged* event);

private:
    void RegisterEventCallbacks();
    void UnregisterEventCallbacks();
};
