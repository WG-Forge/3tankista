#include "game.h"

#include "game_configuration.h"

Game::Game(const std::string& title)
    : gameTitle(title)
{
}

void Game::Initialize()
{
    this->ChangeState(GameState::INITIALIZED);
}

void Game::Run()
{
    ecs::Ecs_Engine->Update(DELTA_TIME_STEP);

    this->UpdateStateMachine();

    ecs::Ecs_Engine->Update(DELTA_TIME_STEP);

    this->UpdateStateMachine();

    ecs::Ecs_Engine->Update(DELTA_TIME_STEP);

    this->UpdateStateMachine();

    ecs::Ecs_Engine->Update(DELTA_TIME_STEP);

    this->UpdateStateMachine();
}

void Game::InitializeECS()
{
    ecs::Initialize();
}

void Game::OnLoginGame(const GameLoginEvent* event)
{
    this->PushState(GameState::RESTARTED);
}
