#pragma once

#include "ecs.h"

class GameplaySystem : public ecs::System<GameplaySystem>,
                       public ecs::event::IEventListener
{
public:
    GameplaySystem();
    ~GameplaySystem() override;

private:
    void RegisterEventCallbacks();
    void UnregisterEventCallbacks();
};
