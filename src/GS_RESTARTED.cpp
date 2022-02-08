#include "game.h"

#include "menu_system.h"

void Game::GS_RESTARTED()
{
    // process data from server
}

void Game::GS_RESTARTED_ENTER()
{
    ecs::Ecs_Engine->SendEvent<GameLoginEvent>();
}

void Game::GS_RESTARTED_LEAVE() {}
