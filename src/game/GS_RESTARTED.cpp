#include "game.h"
#include "game_object.h"
#include "systems/menu_system.h"
#include "systems/map_system.h"
#include "systems/server_system.h"

void Game::GS_RESTARTED() {
    ecs::ecsEngine->SendEvent<MapRequestEvent>();
}

void Game::GS_RESTARTED_ENTER()
{
    ecs::ecsEngine->SendEvent<GameLoginEvent>();

}

void Game::GS_INITIALIZED_LEAVE() {}
