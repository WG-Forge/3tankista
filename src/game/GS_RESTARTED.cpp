#include "ecs.h"
#include "game.h"
#include "game_object.h"

void Game::GS_RESTARTED()

{
    // this->PushState(GameState::STARTED);

    ChangeState(GameState::STARTED);
}

void Game::GS_RESTARTED_ENTER()
{
    ecs::ecsEngine->SendEvent<WorldCreateEvent>();
    ecs::ecsEngine->SendEvent<GameLoginEvent>();
}

void Game::GS_INITIALIZED_LEAVE() {}
