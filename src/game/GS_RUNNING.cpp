#include "components/capture_points_component.h"
#include "components/kill_points_component.h"
#include "components/turn_component.h"
#include "game.h"
#include "game_object.h"
#include "systems/win_system.h"

void Game::GS_RUNNING()
{
    WinSystem::UpdateCapturePoints();
    auto                         componentManager = ecs::ecsEngine->GetComponentManager();
    auto                         entityManager    = ecs::ecsEngine->GetEntityManager();
    bool                         isFinished       = false;
    std::pair<int, GameObjectId> winnerId{ 0, 0 };
    if (!componentManager->begin<TurnComponent>()->isFinished())
    {
        for (auto it = componentManager->begin<KillPointsComponent>();
             componentManager->end<KillPointsComponent>() != it;
             ++it)
        {
            //            std::cout
            //                <<
            //                entityManager->GetEntity(it->GetOwner())->GetComponent<CapturePointsComponent>()->GetCapturePoints()
            //                << "\n";
            if (entityManager->GetEntity(it->GetOwner())->GetComponent<CapturePointsComponent>()->GetCapturePoints() >=
                5)
            {
                winnerId   = std::make_pair(winnerId.first + 1, it->GetOwner());
                isFinished = true;
            }
        }
    }
    else
    {
        isFinished = true;
    }
    if (!isFinished)
    {
        ecs::ecsEngine->SendEvent<PlayEvent>();
    }
    else
    {
        bool isDraw = false;
        if (winnerId.first != 1)
        {
            isDraw = true;
        }
        ecs::ecsEngine->SendEvent<GameOverEvent>(isDraw, winnerId.second);
        ecs::ecsEngine->SendEvent<LogoutRequestEvent>();
        ChangeState(GameState::GAMEOVER);
    }
}

void Game::GS_RUNNING_ENTER()
{
    // ecs::ecsEngine->SendEvent<GameFinishedRequestEvent>();
}

void Game::GS_STARTED_LEAVE() {}
