#ifndef SERVER_GAMEALGORITHM_H
#define SERVER_GAMEALGORITHM_H

#include <memory>
#include <vector>

#include "../game_actions/globalgameactions.h"
#include "../game_area/gamearea.h"
#include "../game_area/pathfinder.h"
#include "../game_state/gamestate.h"
#include "../map/map.h"
#include "../tanks/abstracttank.h"
#include "../utility/matrix.hpp"

class GameAlgorithm
{
public:
    GameAlgorithm();
    virtual ~GameAlgorithm(){};

    void Play()
    {
        std::vector<std::shared_ptr<AbstractTank>> currentPlayerTanks;
        std::vector<std::vector<std::shared_ptr<AbstractTank>>> enemies;
        for (auto& now : gameState->GetVehicles())
        {
            if (now.first == gameState->GetCurrentPlayerIdx())
            {
                currentPlayerTanks = &now.second;
                for (auto& vehicle : now.second)
                {
                    gameArea->SetCell(vehicle.GetPosition(), CellState::FRIEND);
                }
            }
            else
            {
                enemies.push_back(&now.second);
                for (auto& vehicle : now.second)
                {
                    gameArea->SetCell(vehicle.GetPosition(), CellState::ENEMY);
                }
            }
        }
        //        SORT(currentPlayerTanks); // according to playing order
        for (auto& tank : currentPlayerTanks)
        {
            // Can attack someone?
            std::shared_ptr<AbstractTank> target = nullptr;
            for (auto& enemyArray : enemies)
            {
                for (auto& potentialTarget : enemyArray)
                {
                    if (tank->CanShoot(potentialTarget->GetPosition()) &&
                        gameState->GetAttackMatrix())
                    {
                        if (target == nullptr ||
                            target->GetHealth() > potentialTarget->GetHealth())
                        {
                            target = potentialTarget;
                        }
                    }
                }
            }
            if (target != nullptr)
            {
                SendShootAction(tank->GetVehicleId(), target->GetPosition());
            }
            else
            {
                // Is on the base?
                bool isOnTheBase = false;
                for (auto& basePosition :
                     map->GetContent().GetBase().GetHexes())
                {
                    isOnTheBase |= basePosition == tank->GetPosition();
                }
                if (isOnTheBase)
                    continue; // STAY
                // Move to the nearest base
                pathFinder.SetStartPoint(tank->GetPosition());
                Vector3i nearestBasePos =
                    map->GetContent().GetBase().GetHexes().front();
                for (auto& basePosition :
                     map->GetContent().GetBase().GetHexes())
                {
                    if (pathFinder.GetDistance(nearestBasePos) >
                        pathFinder.GetDistance(basePosition))
                    {
                        nearestBasePos = basePosition;
                    }
                }
                auto path = pathFinder.GetShortestPath(nearestBasePos);
                gameArea->SetCell(tank->GetPosition(), CellState::EMPTY);
                gameArea->SetCell(path[tank->GetSpeed() - 1],
                                  CellState::FRIEND);
                MOVE(tank, path[tank->GetSpeed() - 1]);
            }
        }
    }

private:
    std::shared_ptr<GameArea>  gameArea;
    std::shared_ptr<GameState> gameState;
    std::shared_ptr<Map>       map;
    PathFinder                 pathFinder;
};

#endif // SERVER_GAMEALGORITHM_H
