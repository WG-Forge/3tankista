#include "game.h"
#include "game_object.h"

#include "systems/render_system.h"

void Game::GS_STARTED()
{
    ChangeState(GameState::RUNNING);
}

void Game::GS_STARTED_ENTER()
{
    ecs::ecsEngine->SendEvent<MapRequestEvent>();
    ecs::ecsEngine->SendEvent<GameStateRequestEvent>();
}

void Game::GS_RESTARTED_LEAVE() {}
