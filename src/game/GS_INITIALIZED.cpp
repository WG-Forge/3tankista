#include "game.h"

#include "systems/menu_system.h"
#include "systems/render_system.h"
#include "systems/server_system.h"

#include "entities/map.h"
#include "entities/obstacle.h"

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

    //    GameObjectId mapId =
    //        ecs::ecsEngine->GetEntityManager()->CreateEntity<Map>();

    //    ecs::IEntity* map =
    //    ecs::ecsEngine->GetEntityManager()->GetEntity(mapId);

    GameObjectId obstacleId =
        ecs::ecsEngine->GetEntityManager()->CreateEntity<Obstacle>();

    ecs::IEntity* obstacle =
        ecs::ecsEngine->GetEntityManager()->GetEntity(obstacleId);

    ChangeState(GameState::RESTARTED);
}

void Game::GS_INITIALIZED_ENTER()
{
    this->InitializeECS();

    this->InitializeGLFW();
}
