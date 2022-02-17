#include "game.h"

#include "systems/map_system.h"
#include "systems/menu_system.h"
#include "systems/server_system.h"

void Game::GS_INITIALIZED()
{
    MenuSystem* MeS = ecs::ecsEngine->GetSystemManager()->AddSystem<MenuSystem>();

    ServerSystem* SeS = ecs::ecsEngine->GetSystemManager()->AddSystem<ServerSystem>("wgforge-srv.wargaming.net", "443");
    MapSystem*    MaS = ecs::ecsEngine->GetSystemManager()->AddSystem<MapSystem>();

    ecs::ecsEngine->GetSystemManager()->UpdateSystemWorkOrder();

    ChangeState(GameState::RESTARTED);
}

void Game::GS_INITIALIZED_ENTER()
{
    this->InitializeECS();
}
