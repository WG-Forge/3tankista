#include "game.h"
#include "game_object.h"

void Game::GS_GAMEFINISHED()
{
    this->HideWindow();
    ChangeState(GameState::RESTARTED);
}

void Game::GS_GAMEFINISHED_ENTER() {}

void Game::GS_RUNNING_LEAVE() {}
