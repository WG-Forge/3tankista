#include "game.h"
#include "game_object.h"

void Game::GS_GAMEOVER()
{
    ecs::ecsEngine->SendEvent<QuitGameEvent>();
}

void Game::GS_GAMEOVER_ENTER()
{
    RegisterEventCallback(&Game::OnQuitGame);
}

void Game::GS_RUNNING_LEAVE()
{
    UnregisterEventCallback(&Game::OnQuitGame);
}
