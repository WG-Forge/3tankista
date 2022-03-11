#include "menu_system.h"

#include <iostream>

#include "components/adapter_player_id_component.h"
#include "components/capture_points_component.h"
#include "components/kill_points_component.h"
#include "components/name_component.h"
#include "components/turn_component.h"
#include "game/game_events.h"

#include "ecs.h"

#include "nana/gui.hpp"
#include "nana/gui/widgets/button.hpp"
#include "nana/gui/widgets/label.hpp"

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

    inputbox inbox(form{}, "Please input <bold>login information</>.", "Sign up");

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

    nana::form fm{ nana::rectangle{ nana::API::make_center(300, 250) } };
    fm.caption("Results");

    nana::label  nameTitle{ fm, "Name" };
    nana::label  capturePointsTitle{ fm, "Capture points" };
    nana::label  killPointsTitle{ fm, "Kill points" };
    nana::button buttonOk{ fm, "\u2714 OK" };

    nana::place plc{ fm };

    plc.div("<><weight=80% vertical<>"
            "<weight=80% vertical "
            "<information grid=[3,4] gap=10>  "
            "<weight=25 gap=20 buttons> ><>><>");

    plc.field("information") << nameTitle.handle() << capturePointsTitle.handle() << killPointsTitle.handle();

    auto componentManager = ecs::ecsEngine->GetComponentManager();
    auto entityManager    = ecs::ecsEngine->GetEntityManager();
    for (auto it = componentManager->begin<KillPointsComponent>(); componentManager->end<KillPointsComponent>() != it;
         ++it)
    {
        auto player = entityManager->GetEntity(it->GetOwner());

        nana::label* name = new nana::label{ fm, player->GetComponent<NameComponent>()->GetName() };
        nana::label* capturePoints =
            new nana::label{ fm, std::to_string(player->GetComponent<CapturePointsComponent>()->GetCapturePoints()) };
        nana::label* killPoints =
            new nana::label{ fm, std::to_string(player->GetComponent<KillPointsComponent>()->GetKillPoints()) };

        plc.field("information") << name->handle() << capturePoints->handle() << killPoints->handle();
    }

    plc.field("buttons") << buttonOk.handle();

    plc.collocate();

    fm.show();

    nana::exec();
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
