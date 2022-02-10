#pragma once

#include "game_events.h"
#include "models.h"

#include "ecs.h"

class MenuSystem : public ecs::System<MenuSystem>,
                   public ecs::event::IEventListener
{
public:
    MenuSystem();
    ~MenuSystem();

    const LoginRequestModel RequestLoginCredentials();

    void OnLoginRequest(const GameLoginEvent* event);

private:
    void RegisterEventCallbacks();
    void UnregisterEventCallbacks();
};
