#pragma once

#include "ecs.h"
#include "game/game_events.h"

class TurnSystem : public ecs::System<TurnSystem>, public ecs::event::IEventListener
{
public:
    TurnSystem();
    ~TurnSystem() override;

    void OnTurnResponseEvent(const TurnResponseEvent* event);

private:
    void RegisterEventCallbacks();
    void UnregisterEventCallbacks();
};
