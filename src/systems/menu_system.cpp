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
    if (event->isDraw)
    {
        std::cout << "It is draw. All players lost\n";
    }
    else
    {
        auto componentManager = ecs::ecsEngine->GetComponentManager();
        auto playerAdapter    = componentManager->begin<AdapterPlayerIdComponent>();
        auto winner           = ecs::ecsEngine->GetEntityManager()->GetEntity(event->winner);
        std::cout << "Winner:\n"
                  << winner->GetComponent<NameComponent>()->GetName() << "\n"
                  << "Capture points: " << winner->GetComponent<CapturePointsComponent>()->GetCapturePoints() << "\n"
                  << "Kill points: " << winner->GetComponent<KillPointsComponent>()->GetKillPoints() << "\n";
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
