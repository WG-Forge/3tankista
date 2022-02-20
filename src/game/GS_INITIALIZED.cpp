#include "game.h"

#include "systems/menu_system.h"
#include "systems/render_system.h"
#include "systems/server_system.h"

#include "entities/base.h"
#include "entities/map.h"
#include "entities/obstacle.h"
#include "entities/spawn.h"
#include "entities/tank.h"

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

    ecs::ecsEngine->GetEntityManager()->CreateEntity<Map>();

    ecs::ecsEngine->GetEntityManager()->CreateEntity<Base>(
        2, Vector3i{ 0, 0, 0 }, Color(0.55f, 0.84f, 0.56f, 1.0f));

    for (int i = 2; i < 11; ++i)
    {
        if (i == 4)
        {
            continue;
        }

        ecs::ecsEngine->GetEntityManager()->CreateEntity<Obstacle>(
            Vector3i(0, i, 0));
    }

    for (int i = 2; i < 11; ++i)
    {
        if (i == 4)
        {
            continue;
        }

        ecs::ecsEngine->GetEntityManager()->CreateEntity<Obstacle>(
            Vector3i(0, -i, 0));
    }

    for (int i = 2; i < 11; ++i)
    {
        if (i == 4)
        {
            continue;
        }

        ecs::ecsEngine->GetEntityManager()->CreateEntity<Obstacle>(
            Vector3i(i, 0, 0));
    }

    for (int i = 2; i < 11; ++i)
    {
        if (i == 4)
        {
            continue;
        }

        ecs::ecsEngine->GetEntityManager()->CreateEntity<Obstacle>(
            Vector3i(-i, 0, 0));
    }

    for (int i = 2; i < 11; ++i)
    {
        if (i == 4)
        {
            continue;
        }

        ecs::ecsEngine->GetEntityManager()->CreateEntity<Obstacle>(
            Vector3i(i, -i, 0));
    }

    for (int i = 2; i < 11; ++i)
    {
        if (i == 4)
        {
            continue;
        }

        ecs::ecsEngine->GetEntityManager()->CreateEntity<Obstacle>(
            Vector3i(-i, i, 0));
    }

    for (int i = 0; i < 5; ++i)
    {
        ecs::ecsEngine->GetEntityManager()->CreateEntity<Spawn>(
            Vector3i{ 10, -3 - i, 0 }, Color(0.88f, 0.44f, 0.86f, 1.0f));
    }

    for (int i = 0; i < 5; ++i)
    {
        ecs::ecsEngine->GetEntityManager()->CreateEntity<Spawn>(
            Vector3i{ -7 + i, -3 - i, 0 }, Color(1.0f, 0.55f, 0.26f, 1.0f));
    }

    for (int i = 0; i < 5; ++i)
    {
        ecs::ecsEngine->GetEntityManager()->CreateEntity<Spawn>(
            Vector3i{ -7 + i, 10, 0 }, Color(0.31f, 0.75f, 0.89f, 1.0f));
    }

    ecs::ecsEngine->GetEntityManager()->CreateEntity<Tank>(
        Vector3i(10, -3, 0), "textures/at_spg.png");

    ecs::ecsEngine->GetEntityManager()->CreateEntity<Tank>(
        Vector3i(10, -4, 0), "textures/light.png");

    ecs::ecsEngine->GetEntityManager()->CreateEntity<Tank>(
        Vector3i(10, -5, 0), "textures/heavy.png");

    ecs::ecsEngine->GetEntityManager()->CreateEntity<Tank>(
        Vector3i(10, -6, 0), "textures/medium.png");

    ecs::ecsEngine->GetEntityManager()->CreateEntity<Tank>(Vector3i(10, -7, 0),
                                                           "textures/spg.png");

    ecs::ecsEngine->GetEntityManager()->CreateEntity<Tank>(
        Vector3i(-7, -3, 0), "textures/at_spg.png");

    ecs::ecsEngine->GetEntityManager()->CreateEntity<Tank>(
        Vector3i(-6, -4, 0), "textures/light.png");

    ecs::ecsEngine->GetEntityManager()->CreateEntity<Tank>(
        Vector3i(-5, -5, 0), "textures/heavy.png");

    ecs::ecsEngine->GetEntityManager()->CreateEntity<Tank>(
        Vector3i(-4, -6, 0), "textures/medium.png");

    ecs::ecsEngine->GetEntityManager()->CreateEntity<Tank>(Vector3i(-3, -7, 0),
                                                           "textures/spg.png");

    ecs::ecsEngine->GetEntityManager()->CreateEntity<Tank>(
        Vector3i(-7, 10, 0), "textures/at_spg.png");

    ecs::ecsEngine->GetEntityManager()->CreateEntity<Tank>(
        Vector3i(-6, 10, 0), "textures/light.png");

    ecs::ecsEngine->GetEntityManager()->CreateEntity<Tank>(
        Vector3i(-5, 10, 0), "textures/heavy.png");

    ecs::ecsEngine->GetEntityManager()->CreateEntity<Tank>(
        Vector3i(-4, 10, 0), "textures/medium.png");

    ecs::ecsEngine->GetEntityManager()->CreateEntity<Tank>(Vector3i(-3, 10, 0),
                                                           "textures/spg.png");

    ecs::ecsEngine->GetSystemManager()->UpdateSystemWorkOrder();

    ChangeState(GameState::RESTARTED);
}

void Game::GS_INITIALIZED_ENTER()
{
    this->InitializeECS();

    this->InitializeGLFW();
}
