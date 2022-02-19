#include "game.h"
#include "game_object.h"

void Game::GS_GAMEOVER()
{

}

void Game::GS_GAMEOVER_ENTER()
{
    std::cout << "end of game"
              << "\n";
}

void Game::GS_RUNNING_LEAVE() {}
