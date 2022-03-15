#pragma once

#include "ecs.h"
#include "game/game_events.h"

class AttackMatrixSystem : public ecs::System<AttackMatrixSystem>, public ecs::event::IEventListener
{
public:
    AttackMatrixSystem();
    ~AttackMatrixSystem() override;

    void OnShootResponseEvent(const ShootResponseEvent* event);

private:
    void RegisterEventCallbacks();
    void UnregisterEventCallbacks();
};
