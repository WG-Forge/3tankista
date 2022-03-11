#include "game.h"
#include "game_object.h"

void Game::GS_GAMEFINISHED()
{
    //    ecs::ecsEngine->SendEvent<QuitGameEvent>();
    this->HideWindow();
    ChangeState(GameState::RESTARTED);
}

void Game::GS_GAMEFINISHED_ENTER()
{
    //    RegisterEventCallback(&Game::OnQuitGame);
}

void Game::GS_RUNNING_LEAVE()
{
    //    UnregisterEventCallback(&Game::OnQuitGame);
}
