#include "game.h"

#include "menu_system.h"

void Game::GS_RESTARTED() {}

void Game::GS_RESTARTED_ENTER()
{
    ecs::Ecs_Engine->SendEvent<GameLoginEvent>();
}

void Game::GS_INITIALIZED_LEAVE() {}
