#pragma once

#include "ecs.h"
#include "game/game_events.h"

class CatapultSystem : public ecs::System<CatapultSystem>, public ecs::event::IEventListener
{
public:
    CatapultSystem();
    ~CatapultSystem() override;

    void OnMoveResponse(const MoveResponseEvent* event);
    void OnShootResponse(const ShootResponseEvent* event);

private:
    void RegisterEventCallbacks();
    void UnregisterEventCallbacks();
};
