#pragma once

#include "ecs.h"
#include "game/game_events.h"

class MoveSystem : public ecs::System<MoveSystem>, public ecs::event::IEventListener
{
public:
    MoveSystem();
    ~MoveSystem() override;

    void OnMoveResponse(const MoveResponseEvent* event);

private:
    void RegisterEventCallbacks();
    void UnregisterEventCallbacks();
};
