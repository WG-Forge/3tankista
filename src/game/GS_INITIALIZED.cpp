#include "game.h"

#include "systems/action_system.h"
#include "systems/adapter_system.h"
#include "systems/game_create/game_state_system.h"
#include "systems/gameplay_system.h"
#include "systems/health_system.h"
#include "systems/login_system.h"
#include "systems/game_create/map_system.h"
#include "systems/menu_system.h"
#include "systems/move_system.h"
#include "systems/respawn_system.h"
#include "systems/server/server_system.h"
#include "systems/win_system.h"

void Game::GS_INITIALIZED()
{
    auto* LoS = ecs::ecsEngine->GetSystemManager()->AddSystem<LoginSystem>();
    auto* MeS = ecs::ecsEngine->GetSystemManager()->AddSystem<MenuSystem>();
    auto* SeS = ecs::ecsEngine->GetSystemManager()->AddSystem<ServerSystem>("wgforge-srv.wargaming.net", "443");
    auto* MaS = ecs::ecsEngine->GetSystemManager()->AddSystem<MapSystem>();
    auto* HeS = ecs::ecsEngine->GetSystemManager()->AddSystem<HealthSystem>();
    auto* MoS = ecs::ecsEngine->GetSystemManager()->AddSystem<MoveSystem>();
    auto* GpS = ecs::ecsEngine->GetSystemManager()->AddSystem<GameplaySystem>();
    auto* GsS = ecs::ecsEngine->GetSystemManager()->AddSystem<GameStateSystem>();
    auto* AcS = ecs::ecsEngine->GetSystemManager()->AddSystem<ActionSystem>();
    auto* AdS = ecs::ecsEngine->GetSystemManager()->AddSystem<AdapterSystem>();
    auto* ReS = ecs::ecsEngine->GetSystemManager()->AddSystem<RespawnSystem>();
    auto* WiS = ecs::ecsEngine->GetSystemManager()->AddSystem<WinSystem>();

    ecs::ecsEngine->GetSystemManager()->UpdateSystemWorkOrder();
    ChangeState(GameState::RESTARTED);
}

void Game::GS_INITIALIZED_ENTER()

{
    this->InitializeECS();
}
