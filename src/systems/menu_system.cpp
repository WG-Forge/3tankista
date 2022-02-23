#include "menu_system.h"

#include <iostream>

#include "components/adapter_player_id_component.h"
#include "components/capture_points_component.h"
#include "components/kill_points_component.h"
#include "components/name_component.h"
#include "components/turn_component.h"
#include "ecs.h"
#include "game/game_events.h"

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

void MenuSystem::OnGameOver(const GameOverEvent* event)
{
    if (event->winners.size() > 1)
    {
        std::cout << "It is draw for players:\n";
        for (auto& winner : event->winners)
        {
            std::cout
                << "Player:\n"
                << ecs::ecsEngine->GetEntityManager()->GetEntity(winner.first)->GetComponent<NameComponent>()->GetName()
                << "\n"
                << "Capture points: " << winner.second.first << "\n"
                << "Kill points: " << winner.second.second << "\n";
        }
        std::cout << "Other players lost\n";
    }
    else if (event->winners.size() == 1)
    {
        auto winner = ecs::ecsEngine->GetEntityManager()->GetEntity(event->winners[0].first);
        std::cout << "Winner:\n"
                  << winner->GetComponent<NameComponent>()->GetName() << "\n"
                  << "Capture points: " << event->winners[0].second.first << "\n"
                  << "Kill points: " << event->winners[0].second.second << "\n";
    }
}

void MenuSystem::RegisterEventCallbacks()
{
    RegisterEventCallback(&MenuSystem::OnLoginRequest);
    RegisterEventCallback(&MenuSystem::OnGameOver);
}

void MenuSystem::UnregisterEventCallbacks()
{
    UnregisterEventCallback(&MenuSystem::OnLoginRequest);
    UnregisterEventCallback(&MenuSystem::OnGameOver);
}
