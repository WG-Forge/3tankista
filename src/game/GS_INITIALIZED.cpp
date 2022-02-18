#include "game.h"

#include "systems/menu_system.h"
#include "systems/render_system.h"
#include "systems/server_system.h"

#include "entities/base.h"
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

    GameObjectId baseId =
        ecs::ecsEngine->GetEntityManager()->CreateEntity<Base>();

    ecs::IEntity* base = ecs::ecsEngine->GetEntityManager()->GetEntity(baseId);

    for (int i = 2; i < 11; ++i)
    {
        if (i == 4)
        {
            continue;
        }

        GameObjectId obstacleId =
            ecs::ecsEngine->GetEntityManager()->CreateEntity<Obstacle>(
                Vector3i(0, i, 0));

        ecs::IEntity* obstacle =
            ecs::ecsEngine->GetEntityManager()->GetEntity(obstacleId);
    }

    for (int i = 2; i < 11; ++i)
    {
        if (i == 4)
        {
            continue;
        }

        GameObjectId obstacleId =
            ecs::ecsEngine->GetEntityManager()->CreateEntity<Obstacle>(
                Vector3i(0, -i, 0));

        ecs::IEntity* obstacle =
            ecs::ecsEngine->GetEntityManager()->GetEntity(obstacleId);
    }

    for (int i = 2; i < 11; ++i)
    {
        if (i == 4)
        {
            continue;
        }

        GameObjectId obstacleId =
            ecs::ecsEngine->GetEntityManager()->CreateEntity<Obstacle>(
                Vector3i(i, 0, 0));

        ecs::IEntity* obstacle =
            ecs::ecsEngine->GetEntityManager()->GetEntity(obstacleId);
    }

    for (int i = 2; i < 11; ++i)
    {
        if (i == 4)
        {
            continue;
        }

        GameObjectId obstacleId =
            ecs::ecsEngine->GetEntityManager()->CreateEntity<Obstacle>(
                Vector3i(-i, 0, 0));

        ecs::IEntity* obstacle =
            ecs::ecsEngine->GetEntityManager()->GetEntity(obstacleId);
    }

    for (int i = 2; i < 11; ++i)
    {
        if (i == 4)
        {
            continue;
        }

        GameObjectId obstacleId =
            ecs::ecsEngine->GetEntityManager()->CreateEntity<Obstacle>(
                Vector3i(i, -i, 0));

        ecs::IEntity* obstacle =
            ecs::ecsEngine->GetEntityManager()->GetEntity(obstacleId);
    }

    for (int i = 2; i < 11; ++i)
    {
        if (i == 4)
        {
            continue;
        }

        GameObjectId obstacleId =
            ecs::ecsEngine->GetEntityManager()->CreateEntity<Obstacle>(
                Vector3i(-i, i, 0));

        ecs::IEntity* obstacle =
            ecs::ecsEngine->GetEntityManager()->GetEntity(obstacleId);
    }

    GameObjectId mapId =
        ecs::ecsEngine->GetEntityManager()->CreateEntity<Map>();

    ecs::IEntity* map = ecs::ecsEngine->GetEntityManager()->GetEntity(mapId);

    ecs::ecsEngine->GetSystemManager()->UpdateSystemWorkOrder();

    ChangeState(GameState::RESTARTED);
}

void Game::GS_INITIALIZED_ENTER()
{
    this->InitializeECS();

    this->InitializeGLFW();
}
