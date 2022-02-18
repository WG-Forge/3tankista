#pragma once

#include "ecs.h"
#include "game/game_events.h"

class GameStateSystem : public ecs::System<GameStateSystem>, public ecs::event::IEventListener
{
public:
    GameStateSystem();
    ~GameStateSystem() override;

    void OnGameStateResponseEvent(const GameStateResponseEvent* event);
    void OnGameFinishedRequestEvent(const GameFinishedRequestEvent* event);
    void OnWorldCreateEvent(const WorldCreateEvent* event);

private:
    void RegisterEventCallbacks();
    void UnregisterEventCallbacks();
};
