#include "menu_system.h"

#include <iostream>

#include "components/adapter_player_id_component.h"
#include "components/capture_points_component.h"
#include "components/kill_points_component.h"
#include "components/name_component.h"
#include "components/player_id_component.h"
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
    nana::form fm{ nana::API::make_center(300, 250) };

    nana::place plc(fm);

    fm.caption("Results");

    plc.div("<><weight = 80 % vertical<>"
            "<weight = 70 % vertical"
            "<vertical title grid=[3,1]>"
            "<vertical information grid=[3,3]>"
            "<<margin=[0,0,0,200]>weight=25 gap=10 button>> <>> <> ");
    std::shared_ptr<nana::label> playerTitle        = std::make_shared<nana::label>(fm, "Player");
    std::shared_ptr<nana::label> capturePointsTitle = std::make_shared<nana::label>(fm, "Caption points");
    std::shared_ptr<nana::label> killPointsTitle    = std::make_shared<nana::label>(fm, "Kill points");

    plc.field("title") << playerTitle->handle() << capturePointsTitle->handle() << killPointsTitle->handle();

    std::vector<std::shared_ptr<nana::label>> labels;
    for (auto& winner : event->winners)
    {
        auto entity = ecs::ecsEngine->GetEntityManager()->GetEntity(winner.first);
        labels.emplace_back(new nana::label{ fm });
        labels.back()->format(true);
        labels.back()->caption(
            ("<bold=true color=0x09943C>" + entity->GetComponent<NameComponent>()->GetName() + "</>"));
        plc.field("information") << labels.back()->handle();
        labels.emplace_back(new nana::label{ fm, std::to_string(winner.second.first) });
        plc.field("information") << labels.back()->handle();
        labels.emplace_back(new nana::label{ fm, std::to_string(winner.second.second) });
        plc.field("information") << labels.back()->handle();
    }

    auto componentManager = ecs::ecsEngine->GetComponentManager();
    auto entityManager    = ecs::ecsEngine->GetEntityManager();
    for (auto it = componentManager->begin<KillPointsComponent>(); componentManager->end<KillPointsComponent>() != it;
         ++it)
    {
        auto player         = entityManager->GetEntity(it->GetOwner());
        bool isPLayerWinner = false;
        for (auto& winner : event->winners)
        {
            if (winner.first == player->GetComponent<PlayerIdComponent>()->GetPlayerId())
            {
                isPLayerWinner = true;
                break;
            }
        }

        if (!isPLayerWinner)
        {
            std::pair<int, int> winPoints{ player->GetComponent<CapturePointsComponent>()->GetCapturePoints(),
                                           it->GetKillPoints() };
            labels.emplace_back(new nana::label{ fm });
            labels.back()->format(true);
            labels.back()->caption(
                ("<bold=true color=0x8A0D0D>" + player->GetComponent<NameComponent>()->GetName() + "</>"));
            plc.field("information") << labels.back()->handle();
            labels.emplace_back(new nana::label{ fm, std::to_string(winPoints.first) });
            plc.field("information") << labels.back()->handle();
            labels.emplace_back(new nana::label{ fm, std::to_string(winPoints.second) });
            plc.field("information") << labels.back()->handle();
        }
    }

    std::shared_ptr<nana::button> buttonOk = std::make_shared<nana::button>(fm, "\u2714 OK");

    buttonOk->events().click(
        [&]()
        {
            fm.close();
            ecs::ecsEngine->SendEvent<QuitGameEvent>();
        });

    plc.field("button") << buttonOk->handle();

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
