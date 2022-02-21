#include "components/attack_matrix_component.h"
#include "components/capture_points_component.h"
#include "components/kill_points_component.h"
#include "components/turn_component.h"
#include "game.h"
#include "systems/win_system.h"

void Game::GS_RUNNING()
{
    WinSystem::UpdateCapturePoints();
    auto                         componentManager = ecs::ecsEngine->GetComponentManager();
    auto                         entityManager    = ecs::ecsEngine->GetEntityManager();
    bool                         isFinished       = false;
    std::pair<int, GameObjectId> winnerId{ 0, 0 };
    auto attackMatrixComponent = componentManager->begin<AttackMatrixComponent>().operator->();
    auto attackMatrix          = attackMatrixComponent->GetAttackMatrix();
    attackMatrixComponent->SetAttackMatrix(attackMatrix);
    for (auto& [key, value] : attackMatrixComponent->GetAttackMatrix())
    {
        std::cout << key << " {";
        for (auto& id : value)
        {
            std::cout << id << ", ";
        }
        std::cout << "}\n" << std::flush;
    }
    if (!componentManager->begin<TurnComponent>()->isFinished())
    {
        // std::cout<<"GS "<<componentManager->begin<TurnComponent>()->GetCurrentTurn()<<"\n";
        for (auto it = componentManager->begin<KillPointsComponent>();
             componentManager->end<KillPointsComponent>() != it;
             ++it)
        {
            std::cout << "kp " << it->GetKillPoints() << "\n";
            std::cout
                << "cp "
                << entityManager->GetEntity(it->GetOwner())->GetComponent<CapturePointsComponent>()->GetCapturePoints()
                << "\n"
                << std::flush;
            if (entityManager->GetEntity(it->GetOwner())->GetComponent<CapturePointsComponent>()->GetCapturePoints() >=
                5)
            {
                winnerId   = std::make_pair(winnerId.first + 1, it->GetOwner());
                isFinished = true;
            }
        }
        if (winnerId.first != 1)
        {
            int max = 0;
            for (auto it = componentManager->begin<KillPointsComponent>();
                 componentManager->end<KillPointsComponent>() != it;
                 ++it)
            {
                if (max < it->GetKillPoints())
                {
                    max = it->GetKillPoints();
                }
            }
            winnerId = {};
            for (auto it = componentManager->begin<KillPointsComponent>();
                 componentManager->end<KillPointsComponent>() != it;
                 ++it)
            {
                if (max == it->GetKillPoints())
                {
                    winnerId = std::make_pair(winnerId.first + 1, it->GetOwner());
                }
            }
        }
    }
    else
    {
        for (auto it = componentManager->begin<KillPointsComponent>();
             componentManager->end<KillPointsComponent>() != it;
             ++it)
        {
            std::cout << "kp " << it->GetKillPoints() << "\n";
            std::cout
                << "cp "
                << entityManager->GetEntity(it->GetOwner())->GetComponent<CapturePointsComponent>()->GetCapturePoints()
                << "\n"
                << std::flush;
            if (entityManager->GetEntity(it->GetOwner())->GetComponent<CapturePointsComponent>()->GetCapturePoints() >=
                5)
            {
                winnerId   = std::make_pair(winnerId.first + 1, it->GetOwner());
                isFinished = true;
            }
        }
        if (!isFinished)
        {
            int max = 0;
            for (auto it = componentManager->begin<KillPointsComponent>();
                 componentManager->end<KillPointsComponent>() != it;
                 ++it)
            {
                if (max < it->GetKillPoints())
                {
                    max = it->GetKillPoints();
                }
            }
            for (auto it = componentManager->begin<KillPointsComponent>();
                 componentManager->end<KillPointsComponent>() != it;
                 ++it)
            {
                if (max == it->GetKillPoints())
                {
                    winnerId = std::make_pair(winnerId.first + 1, it->GetOwner());
                }
            }
        }

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
        // ecs::ecsEngine->SendEvent<GameStateRequestEvent>();
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
