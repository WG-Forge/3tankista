#ifndef SERVER_GAMEALGORITHM_H
#define SERVER_GAMEALGORITHM_H

#include "../game_actions/globalgameactions.h"
#include "../game_area/gamearea.h"
#include "../game_area/pathfinder.h"
#include "../game_state/gamestate.h"
#include "../map/map.h"
#include "../tanks/abstracttank.h"
#include "../utility/matrix.hpp"
#include <algorithm>
#include <memory>
#include <utility>
#include <vector>

class GameAlgorithm
{
public:
    GameAlgorithm(std::shared_ptr<GameArea> gameArea, std::shared_ptr<Map> map)
        : gameArea(std::move(gameArea))
        , gameState(nullptr)
        , map(std::move(map))
        , pathFinder(new PathFinder(this->gameArea))
    {
    }
    virtual ~GameAlgorithm(){};

    // True, if tank can attack enemy
    bool CheckNeutrality(std::shared_ptr<AbstractTank> playerTank,
                         std::shared_ptr<AbstractTank> enemyTank)
    {
        bool neutrality    = false;
        auto attackMatrix  = gameState->GetAttackMatrix();
        int  tankPlayerId  = playerTank->GetPlayerId();
        int  enemyPlayerId = enemyTank->GetPlayerId();
        int  thirdPlayerId = -1;
        for (const auto& [key, value] : attackMatrix)
        {
            if (key != enemyPlayerId && key != tankPlayerId)
            {
                thirdPlayerId = key;
                break;
            }
        }
        if (std::find(attackMatrix[enemyPlayerId].begin(),
                      attackMatrix[enemyPlayerId].end(),
                      tankPlayerId) != attackMatrix[enemyPlayerId].end() ||
            std::find(attackMatrix[thirdPlayerId].begin(),
                      attackMatrix[thirdPlayerId].end(),
                      enemyPlayerId) == attackMatrix[thirdPlayerId].end())
        {
            neutrality = true;
        }
        return neutrality;
    }

    void Play()
    {
        gameArea->ClearMap();
        std::vector<std::shared_ptr<AbstractTank>> currentPlayerTanks;
        std::vector<std::vector<std::shared_ptr<AbstractTank>>> enemies;
        for (auto& now : gameState->GetVehicles())
        {
            if (now.first == gameState->GetCurrentPlayerIdx())
            {
                currentPlayerTanks = now.second;
                for (auto& vehicle : now.second)
                {
                    gameArea->SetCell(vehicle->GetPosition(),
                                      CellState::FRIEND);
                }
            }
            else
            {
                enemies.push_back(now.second);
                for (auto& vehicle : now.second)
                {
                    gameArea->SetCell(vehicle->GetPosition(), CellState::ENEMY);
                }
            }
        }
        std::sort(currentPlayerTanks.begin(),
                  currentPlayerTanks.end(),
                  [](const std::shared_ptr<AbstractTank>& lhs,
                     const std::shared_ptr<AbstractTank>& rhs)
                  { return *lhs < *rhs; });
        for (auto& tank : currentPlayerTanks)
        {
            // Can attack someone?
            std::shared_ptr<AbstractTank> target = nullptr;
            for (auto& enemyArray : enemies)
            {
                for (auto& potentialTarget : enemyArray)
                {
                    if (tank->CanShoot(potentialTarget->GetPosition()) &&
                        CheckNeutrality(tank, potentialTarget)/* check neutrality rule &&
                        gameState->GetAttackMatrix()*/)
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
                tank->Shoot(target->GetPosition());
            }
            else
            {
                // Is on the base?
                bool isOnTheBase = false;
                for (auto& basePosition :
                     map->GetContent().GetBase())
                {
                    isOnTheBase |= basePosition == tank->GetPosition();
                }
                if (isOnTheBase)
                    continue; // STAY
                // Move to the nearest base
                pathFinder->SetStartPoint(tank->GetPosition());
                Vector3i nearestBasePos =
                    map->GetContent().GetBase().front();
                for (auto& basePosition :
                     map->GetContent().GetBase())
                {
                    if (pathFinder->GetDistance(nearestBasePos) == NOPATH ||
                        (pathFinder->GetDistance(nearestBasePos) >
                             pathFinder->GetDistance(basePosition) &&
                         pathFinder->GetDistance(basePosition) != NOPATH))
                    {
                        nearestBasePos = basePosition;
                    }
                }
                if (pathFinder->GetDistance(nearestBasePos) == NOPATH)
                    continue; // STAY
                auto path = pathFinder->GetShortestPath(nearestBasePos);
                if (path.size() == 0)
                    continue; // STAY
                gameArea->SetCell(tank->GetPosition(), CellState::EMPTY);
                gameArea->SetCell(
                    path[std::min((int)path.size(), tank->GetSpeed()) - 1],
                    CellState::FRIEND);
                tank->Move(
                    path[std::min((int)path.size(), tank->GetSpeed()) - 1]);
            }
        }
    }

public:
    void SetGameArea(GameArea* gameArea)
    {
        this->gameArea = std::shared_ptr<GameArea>(gameArea);
    }
    auto&       GetGameArea() { return this->gameArea; }
    const auto& GetGameArea() const { return this->gameArea; }

    void SetGameState(GameState* gameState)
    {
        this->gameState = std::shared_ptr<GameState>(gameState);
    }
    auto&       GetGameState() { return this->gameState; }
    const auto& GetGameState() const { return this->gameState; }

    void        SetMap(Map* map) { this->map = std::shared_ptr<Map>(map); }
    auto&       GetMap() { return this->map; }
    const auto& GetMap() const { return this->map; }

    void SetPathFinder(PathFinder* pathFinder)
    {
        this->pathFinder = std::shared_ptr<PathFinder>(pathFinder);
    }
    auto&       GetPathFinder() { return this->pathFinder; }
    const auto& GetPathFinder() const { return this->pathFinder; }

private:
    std::shared_ptr<GameArea>   gameArea;
    std::shared_ptr<GameState>  gameState;
    std::shared_ptr<Map>        map;
    std::shared_ptr<PathFinder> pathFinder;
};

#endif // SERVER_GAMEALGORITHM_H
