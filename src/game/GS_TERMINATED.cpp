#include "game.h"
#include "game_object.h"

void Game::GS_TERMINATED()
{
    this->Terminate();
}

void Game::GS_TERMINATED_ENTER() {}

void Game::GS_GAMEOVER_LEAVE() {}
