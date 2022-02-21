#include "game.h"

#include "systems/action_system.h"
#include "systems/adapter_system.h"
#include "systems/attack_matrix_system.h"
#include "systems/game_create/game_state_system.h"
#include "systems/game_create/map_system.h"
#include "systems/gameplay_system.h"
#include "systems/health_system.h"
#include "systems/login_system.h"
#include "systems/menu_system.h"
#include "systems/move_system.h"
#include "systems/respawn_system.h"
#include "systems/server/server_system.h"
#include "systems/turn_system.h"
#include "systems/win_system.h"

void Game::GS_INITIALIZED()
{
    auto  systemManager = ecs::ecsEngine->GetSystemManager();
    auto* LoS           = systemManager->AddSystem<LoginSystem>();
    auto* MeS           = systemManager->AddSystem<MenuSystem>();
    auto* SeS           = systemManager->AddSystem<ServerSystem>("wgforge-srv.wargaming.net", "443");
    auto* MaS           = systemManager->AddSystem<MapSystem>();
    auto* HeS           = systemManager->AddSystem<HealthSystem>();
    auto* MoS           = systemManager->AddSystem<MoveSystem>();
    auto* GpS           = systemManager->AddSystem<GameplaySystem>();
    auto* GsS           = systemManager->AddSystem<GameStateSystem>();
    auto* AcS           = systemManager->AddSystem<ActionSystem>();
    auto* AdS           = systemManager->AddSystem<AdapterSystem>();
    auto* ReS           = systemManager->AddSystem<RespawnSystem>();
    auto* WiS           = systemManager->AddSystem<WinSystem>();
    auto* AmS           = systemManager->AddSystem<AttackMatrixSystem>();
    auto* TuS           = systemManager->AddSystem<TurnSystem>();

    systemManager->UpdateSystemWorkOrder();
    ChangeState(GameState::RESTARTED);
}

void Game::GS_INITIALIZED_ENTER()

{
    this->InitializeECS();
}
