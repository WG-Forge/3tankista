#pragma once

#include "ecs.h"
#include "game/game_events.h"

class ActionSystem : public ecs::System<ActionSystem>, public ecs::event::IEventListener
{
public:
    ActionSystem();
    ~ActionSystem() override;

    void OnGameActionsResponseEvent(const GameActionsResponseEvent* event);

private:
    void RegisterEventCallbacks();
    void UnregisterEventCallbacks();
};
