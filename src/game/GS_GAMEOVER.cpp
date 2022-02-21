#include "game.h"
#include "game_object.h"

void Game::GS_GAMEOVER()
{
    ecs::ecsEngine->SendEvent<QuitGameEvent>();
    // ChangeState(GameState::TERMINATED);
}

void Game::GS_GAMEOVER_ENTER()
{
    RegisterEventCallback(&Game::OnQuitGame);
    std::cout << "end of game"
              << "\n"
              << std::flush;
}

void Game::GS_RUNNING_LEAVE()
{
    UnregisterEventCallback(&Game::OnQuitGame);
}
