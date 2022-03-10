#include "menu_system.h"

#include <iostream>

#include "components/adapter_player_id_component.h"
#include "components/capture_points_component.h"
#include "components/kill_points_component.h"
#include "components/name_component.h"
#include "components/turn_component.h"
#include "ecs.h"
#include "game/game_events.h"

#include "nana/gui.hpp"

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

    using namespace nana;

    internationalization i18n;
    // Translate these 2 words into Chinese.
    i18n.set("NANA_BUTTON_OK", "\u2714 OK");
    i18n.set("NANA_BUTTON_CANCEL", "\u2718 CANCEL");

    inputbox::text    nickname("Nickname");
    inputbox::text    password("Password");
    inputbox::text    gameName("Game name");
    inputbox::integer turns("Turns", 45, 0, 9999, 1);
    inputbox::integer players("Players", 1, 0, 6, 1);
    inputbox::boolean observer("Observer", false);

    nickname.tip_string("Input nickname...");
    password.tip_string("Input password...");
    gameName.tip_string("Input game name...");

    password.mask_character('*');

    inputbox inbox(form(), "Please input <bold>login information</>.", "Sign up");

    inbox.verify(
        [&nickname, &gameName, &password](window handle)
        {
            if (nickname.value().empty())
            {
                msgbox mb(handle, "Invalid input");
                mb << "Nickname should not be empty, Please input your nickname.";
                mb.show();
                return false; // verification failedr
            }
            else if (gameName.value().empty())
            {
                msgbox mb(handle, "Invalid input");
                mb << "Game name should not be empty, Please input game name.";
                mb.show();
                return false; // verification failed
            }
            return true; // verified successfully
        });

    if (inbox.show(nickname, password, gameName, turns, players, observer))
    {
        LoginRequestModel credentials;

        credentials.name          = nickname.value();
        credentials.password      = password.value();
        credentials.game          = gameName.value();
        credentials.numberTurns   = turns.value();
        credentials.numberPlayers = players.value();
        credentials.isObserver    = observer.value();

        ecs::ecsEngine->SendEvent<LoginRequestEvent>(credentials);
    }
    else
    {
        ecs::ecsEngine->SendEvent<QuitGameEvent>();
    }

    //    const auto& credentials = this->RequestLoginCredentials();

    //    ecs::ecsEngine->SendEvent<LoginRequestEvent>(credentials);
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
