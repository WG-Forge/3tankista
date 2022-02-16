#include "game.h"

#include "systems/menu_system.h"
#include "systems/render_system.h"
#include "systems/server_system.h"

#include "entities/map.h"

void Game::GS_INITIALIZED()
{
    MenuSystem* MeS =
        ecs::ecsEngine->GetSystemManager()->AddSystem<MenuSystem>();

    ServerSystem* SeS =
        ecs::ecsEngine->GetSystemManager()->AddSystem<ServerSystem>(
            "wgforge-srv.wargaming.net", "443");

    RenderSystem* ReS =
        ecs::ecsEngine->GetSystemManager()->AddSystem<RenderSystem>(
            this->window);

    ecs::ecsEngine->GetSystemManager()->UpdateSystemWorkOrder();

    GameObjectId entityId =
        ecs::ecsEngine->GetEntityManager()->CreateEntity<Map>();

    ecs::IEntity* gameObject =
        ecs::ecsEngine->GetEntityManager()->GetEntity(entityId);

    ChangeState(GameState::RESTARTED);
}

void Game::GS_INITIALIZED_ENTER()
{
    this->InitializeECS();

    this->InitializeGLFW();
}
