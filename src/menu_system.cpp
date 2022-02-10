#include "menu_system.h"

#include <iostream>

#include "game_events.h"

#include "ecs.h"

MenuSystem::MenuSystem()
{
    this->RegisterEventCallbacks();
}

MenuSystem::~MenuSystem()
{
    this->UnregisterEventCallbacks();
}

const LoginRequestModel MenuSystem::RequestLoginCredentials()
{
    LoginRequestModel credentials;

    std::cout << "Write your nickname: ";
    std::cin >> credentials.name;
    std::cout << "Write your password: ";
    std::cin >> credentials.password;
    std::cout << "Write game name: ";
    std::cin >> credentials.game;
    std::cout << "Write number of turns: ";
    std::cin >> credentials.numberTurns;
    std::cout << "Write number of players: ";
    std::cin >> credentials.numberPlayers;
    std::cout << "Write are you observer(y/n): ";
    std::string isObserver = "";
    std::cin >> isObserver;
    credentials.isObserver = isObserver.front() == 'y';

    return credentials;
}

void MenuSystem::OnLoginRequest(const GameLoginEvent* event)
{
    const auto& credentials = this->RequestLoginCredentials();

    ecs::ecsEngine->SendEvent<LoginRequestEvent>(credentials);
}

void MenuSystem::RegisterEventCallbacks()
{
    RegisterEventCallback(&MenuSystem::OnLoginRequest);
}

void MenuSystem::UnregisterEventCallbacks()
{
    UnregisterEventCallback(&MenuSystem::OnLoginRequest);
}
