#include "game.h"

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
    ecs::Ecs_Engine->SendEvent<GameLoginEvent>();

    ecs::Ecs_Engine->Update(1 / 60.0);
}

void Game::InitializeECS()
{
    ecs::Initialize();
}

void Game::OnLoginGame(const GameLoginEvent* event)
{
    this->PushState(GameState::LOGINED);
}
