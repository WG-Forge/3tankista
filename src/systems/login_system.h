#pragma once

#include "ecs.h"
#include "game/game_events.h"

class LoginSystem : public ecs::System<LoginSystem>, public ecs::event::IEventListener

{
public:
    LoginSystem();
    ~LoginSystem() override;

    void OnLoginResponseEvent(const LoginResponseEvent* event);

private:
    void RegisterEventCallbacks();
    void UnregisterEventCallbacks();
};
