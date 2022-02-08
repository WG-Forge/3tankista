#include "game.h"

#include "menu_system.h"
#include "server_system.h"

void Game::GS_INITIALIZED()
{
    MenuSystem* MeS =
        ecs::Ecs_Engine->GetSystemManager()->AddSystem<MenuSystem>();

    ServerSystem* SeS =
        ecs::Ecs_Engine->GetSystemManager()->AddSystem<ServerSystem>(
            "wgforge-srv.wargaming.net", "443");

    ecs::Ecs_Engine->GetSystemManager()->UpdateSystemWorkOrder();

    ChangeState(GameState::RESTARTED);
}

void Game::GS_INITIALIZED_ENTER()
{
    this->InitializeECS();
}
