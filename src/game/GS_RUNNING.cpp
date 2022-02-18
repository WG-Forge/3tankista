#include "game.h"
#include "game_object.h"

void Game::GS_RUNNING()
{
    ecs::ecsEngine->SendEvent<GameFinishedRequestEvent>();
}

void Game::GS_RUNNING_ENTER()
{
    ecs::ecsEngine->SendEvent<GameFinishedRequestEvent>();

}

void Game::GS_STARTED_LEAVE() {}
