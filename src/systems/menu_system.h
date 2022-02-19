#pragma once

#include "game/game_events.h"
#include "game/models/models.h"

#include "ecs.h"

class MenuSystem : public ecs::System<MenuSystem>, public ecs::event::IEventListener
{
public:
    MenuSystem();
    ~MenuSystem();

    const LoginRequestModel RequestLoginCredentials();

    void OnLoginRequest(const GameLoginEvent* event);
    void OnGameOverRequest(const GameOverEvent* event);

private:
    void RegisterEventCallbacks();
    void UnregisterEventCallbacks();
};
