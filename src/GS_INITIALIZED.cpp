#include "game.h"

#include "menu_system.h"

void Game::GS_INITIALIZED()
{
    MenuSystem* MeS =
        ecs::Ecs_Engine->GetSystemManager()->AddSystem<MenuSystem>();

    ecs::Ecs_Engine->GetSystemManager()->UpdateSystemWorkOrder();
}

void Game::GS_INITIALIZED_ENTER()
{
    this->InitializeECS();

    RegisterEventCallback(&Game::OnLoginGame);
}
