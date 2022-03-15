#include "components/attack_matrix_component.h"
#include "components/capture_points_component.h"
#include "components/health_component.h"
#include "components/kill_points_component.h"
#include "components/turn_component.h"
#include "game.h"
#include "systems/health_system.h"
#include "systems/win_system.h"

void Game::GS_RUNNING()
{
    WinSystem::UpdateCapturePoints();
    HealthSystem::HealTanks();
    auto                                                  players          = std::move(WinSystem::GetWinPoints());
    auto                                                  componentManager = ecs::ecsEngine->GetComponentManager();
    bool                                                  isFinished       = false;
    std::vector<std::pair<uint64_t, std::pair<int, int>>> winners;
    if (!componentManager->begin<TurnComponent>()->isFinished())
    {
        // get winners by capture points
        for (auto& player : players)
        {
            if (player.second.first >= 5)
            {
                winners.emplace_back(player.first, player.second);
                isFinished = true;
            }
        }
        // get winners by kill points with capture points
        auto maxKillPoints = WinSystem::GetMaxKillPoints(winners);
        for (int i = 0; i < winners.size(); ++i)
        {
            if (winners[i].second.second != maxKillPoints)
            {
                winners.erase(winners.begin() + i);
            }
        }
    }
    else
    {
        // get winners by kill points
        auto maxKillPoints = WinSystem::GetMaxKillPoints(players);
        for (auto& player : players)
        {
            if (player.second.second == maxKillPoints)
            {
                winners.emplace_back(player.first, player.second);
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
        ecs::ecsEngine->SendEvent<GameOverEvent>(winners);
        ecs::ecsEngine->SendEvent<LogoutRequestEvent>();
        ChangeState(GameState::GAMEFINISHED);
    }
}

void Game::GS_RUNNING_ENTER() {}

void Game::GS_STARTED_LEAVE() {}
