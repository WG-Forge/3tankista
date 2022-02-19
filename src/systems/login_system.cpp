#include "login_system.h"
#include "components/main_player_component.h"

LoginSystem::LoginSystem()
{
    RegisterEventCallbacks();
}

LoginSystem::~LoginSystem()
{
    UnregisterEventCallbacks();
}

void LoginSystem::RegisterEventCallbacks()
{
    RegisterEventCallback(&LoginSystem::OnLoginResponseEvent);
}

void LoginSystem::UnregisterEventCallbacks()
{
    UnregisterEventCallback(&LoginSystem::OnLoginResponseEvent);
}

void LoginSystem::OnLoginResponseEvent(const LoginResponseEvent* event)
{
    auto componentManager = ecs::ecsEngine->GetComponentManager();
    componentManager->begin<MainPlayerComponent>()->SetCurrentPlayerId(event->playerData.index);
}
