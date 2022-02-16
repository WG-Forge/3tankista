#pragma once

#include "ecs.h"

class ActionSystem : public ecs::System<ActionSystem>,
                     public ecs::event::IEventListener
{
public:
    ActionSystem();
    ~ActionSystem() override;

    OnGameActionsResponceEvent();

private:
    void RegisterEventCallbacks();
    void UnregisterEventCallbacks();
};
