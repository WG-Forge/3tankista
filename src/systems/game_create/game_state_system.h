#pragma once

#include "ecs.h"
#include "game/game_events.h"
#include "systems/gameplay_system.h"

class GameStateSystem : public ecs::System<GameStateSystem>, public ecs::event::IEventListener
{
public:
    GameStateSystem();
    ~GameStateSystem() override;

    void OnGameStateResponseEvent(const GameStateResponseEvent* event);
    void OnWorldCreateEvent(const WorldCreateEvent* event);

private:
    void RegisterEventCallbacks();
    void UnregisterEventCallbacks();
};
