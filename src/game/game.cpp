#include "game.h"

#include <utility>

#include "game_configuration.h"

Game::Game(std::string title)
    : gameTitle(std::move(title))
{
}

void Game::Initialize()
{
    this->ChangeState(GameState::INITIALIZED);
}

void Game::Run()
{
    while (this->GetActiveGameState() != GameState::TERMINATED)
    {
        ecs::ecsEngine->Update(DELTA_TIME_STEP);
        this->UpdateStateMachine();
    }
}

void Game::InitializeECS()
{
    ecs::Initialize();
}

void Game::OnLoginGame(const GameLoginEvent* event)
{
    this->PushState(GameState::RESTARTED);
}

void Game::OnGameOverState(const GameOverEvent* event)
{
    this->ChangeState(GameState::GAMEOVER);
}
