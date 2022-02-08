#include "game.h"

#include "menu_system.h"

void Game::GS_LOGINED() {}

void Game::GS_LOGINED_ENTER()
{
    RegisterEventCallback(&Game::OnLoginGame);

    MenuSystem::RequestLoginCredentials();
}

void Game::GS_LOGINED_LEAVE()
{
    UnregisterEventCallback(&Game::OnLoginGame);

    ecs::Ecs_Engine->SendEvent<GameLoginedEvent>();
}
