#pragma once

#include "../third_party/ecs/src/ecs.h"

#include "models.h"

class MenuSystem : public ecs::System<MenuSystem>,
                   protected ecs::event::IEventListener
{
public:
    MenuSystem();
    ~MenuSystem();

    static void RequestLoginCredentials();

private:
    void RegisterEventCallbacks();
    void UnregisterEventCallbacks();
};
