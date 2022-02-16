#pragma once

#include "ecs.h"
#include "game/game_events.h"

class GameStateSystem : public ecs::System<GameStateSystem>,
                        public ecs::event::IEventListener
{
public:
    GameStateSystem();
    ~GameStateSystem() override;

    void OnGameStateResponceEvent(const GameStateResponceEvent* event);
private:
    void RegisterEventCallbacks();
    void UnregisterEventCallbacks();
};
