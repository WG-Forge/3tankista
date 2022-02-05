#pragma once

#include "game_actions/global_game_actions.h"
#include "game_area/game_area.h"
#include "game_area/path_finder.h"
#include "game_state/game_state.h"
#include "map/map.h"
#include "tanks/abstract_tank.h"
#include "utility/matrix.hpp"
#include <algorithm>
#include <memory>
#include <utility>
#include <vector>

class GameAlgorithm
{
public:
    GameAlgorithm() = default;
    GameAlgorithm(std::shared_ptr<GameArea> gameArea, std::shared_ptr<Map> map);
    virtual ~GameAlgorithm() = default;

    /// True, if tank can attack enemy
    bool CheckNeutrality(std::shared_ptr<AbstractTank> playerTank,
                         std::shared_ptr<AbstractTank> enemyTank);

    void Play();

public:
    void SetGameArea(std::shared_ptr<GameArea> gameArea)
    {
        this->gameArea = std::move(gameArea);
    }
    auto&       GetGameArea() { return this->gameArea; }
    const auto& GetGameArea() const { return this->gameArea; }

    void SetGameState(std::unique_ptr<GameState>& gameState)
    {
        this->gameState = std::move(gameState);
    }
    auto&       GetGameState() { return this->gameState; }
    const auto& GetGameState() const { return this->gameState; }

    void        SetMap(std::shared_ptr<Map> map) { this->map = std::move(map); }
    auto&       GetMap() { return this->map; }
    const auto& GetMap() const { return this->map; }

    void SetPathFinder(std::shared_ptr<PathFinder> pathFinder)
    {
        this->pathFinder = std::move(pathFinder);
    }
    auto&       GetPathFinder() { return this->pathFinder; }
    const auto& GetPathFinder() const { return this->pathFinder; }

private:
    std::shared_ptr<GameArea>   gameArea;
    std::unique_ptr<GameState>  gameState;
    std::shared_ptr<Map>        map;
    std::shared_ptr<PathFinder> pathFinder;
};
