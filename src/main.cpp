#include <chrono>
#include <iostream>
#include <thread>
#include <utility>

#include "client.h"
#include "gameactions.h"
#include "gamearea.h"
#include "gameplay/gameplay.hpp"
#include "gamestate.h"
#include "globalgameactions.h"
#include "map.h"
#include "server.h"

#include "singleton.h"

int main()
{
    // LOGIN

    std::string name = "", password = "", game = "";
    int         numberTurns = 0, numberPlayers = 0;
    bool        observer = false;

    std::cout << "Write your nickname: ";
    std::cin >> name;
    std::cout << "Write your password: ";
    std::cin >> password;
    std::cout << "Write game name: ";
    std::cin >> game;
    std::cout << "Write number of turns: ";
    std::cin >> numberTurns;
    std::cout << "Write number of players: ";
    std::cin >> numberPlayers;
    std::cout << "Write are you observer(y/n): ";
    std::string isObserver = "";
    std::cin >> isObserver;
    observer = isObserver.at(0) == 'y' ? true : false;

    Client client;
    auto   isSuccessfully =
        client.Login(ServerModels::LoginRequestModel{ name,
                                                      password,
                                                      game,
                                                      (uint64_t)numberTurns,
                                                      (uint64_t)numberPlayers,
                                                      observer });
    if (!isSuccessfully)
    {
        std::cerr << "Some error occurred while trying to login to the "
                     "server"
                  << std::endl;
    }

    // GET MAP
    auto sent = Singleton<Server>::instance("wgforge-srv.wargaming.net", "443")
                    ->SendAction(Server::Action::MAP, nlohmann::json(""));
    if (!sent)
    {
        std::cerr << "Data wasn't sent" << std::endl;
    }

    Server::Result result = Server::Result::OKEY;
    auto           responce =
        Singleton<Server>::instance("wgforge-srv.wargaming.net", "443")
            ->ReceiveResult(result);
    if (result != Server::Result::OKEY)
    {
        std::cerr << "Map request result: " << static_cast<int>(result) << '\n';
    }
    if (responce.empty())
    {
        std::cerr << "No response was received from the server" << std::endl;
    }
    Map*          map      = new Map(nlohmann::json().parse(responce));
    GameArea*     gameArea = new GameArea(*map);
    GameAlgorithm gameAlgorithm((std::shared_ptr<GameArea>(gameArea)), std::shared_ptr<Map>(map));

    auto gameFinished = false;
    while (!gameFinished)
    {
        // GET GAME STATE
        sent = Singleton<Server>::instance("wgforge-srv.wargaming.net", "443")
                   ->SendAction(Server::Action::GAME_STATE, nlohmann::json(""));
        if (!sent)
        {
            std::cerr << "Data wasn't sent" << std::endl;
        }

        //        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        result = Server::Result::OKEY;
        responce =
            Singleton<Server>::instance("wgforge-srv.wargaming.net", "443")
                ->ReceiveResult(result);
        if (result != Server::Result::OKEY)
        {
            std::cerr << "GameState request result: "
                      << static_cast<int>(result) << '\n';
        }
        if (responce.empty())
        {
            std::cerr << "No response was received from the server"
                      << std::endl;
            continue;
        }
        GameState* gameState = new GameState(nlohmann::json().parse(responce));

        gameFinished = gameState->GetFinished();

        if (gameFinished)
        {
            const auto& winner = std::find_if(
                gameState->GetPlayers().begin(),
                gameState->GetPlayers().end(),
                [&](const Player& player) {
                    return player.GetData().index == gameState->GetWinner();
                });
            std::cerr << "Winner: " << winner->GetData().name << ";"
                      << std::endl
                      << "Capture poitns: "
                      << gameState->GetWinPoints()
                             .at(client.GetData().index)
                             .GetCapture()
                      << ";" << std::endl
                      << "Kill points: "
                      << gameState->GetWinPoints()
                             .at(client.GetData().index)
                             .GetKill()
                      << ";" << std::endl;
            continue;
        }

        gameAlgorithm.SetGameState(gameState);

        if (client.GetData().index == gameState->GetCurrentPlayerIdx())
            gameAlgorithm.Play();

        SendTurnAction();

        //        sent =
        //            Singleton<Server>::instance("wgforge-srv.wargaming.net",
        //            "443")
        //                ->SendAction(Server::Action::GAME_ACTIONS,
        //                nlohmann::json(""));
        //        if (!sent)
        //        {
        //            std::cerr << "Data wasn't sent" << std::endl;
        //        }

        //        result = Server::Result::OKEY;
        //        // какой-то цирк (первый responce всегда пустой)
        //        //
        //        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        //        responce =
        //            Singleton<Server>::instance("wgforge-srv.wargaming.net",
        //            "443")
        //                ->ReceiveResult(result);
        //        if (responce.at(0) != *"{")
        //        {
        //            responce =
        //                Singleton<Server>::instance("wgforge-srv.wargaming.net",
        //                "443")
        //                    ->ReceiveResult(result);
        //        }
        //        if (result != Server::Result::OKEY)
        //        {
        //            std::cerr << "GameActions request result: "
        //                      << static_cast<int>(result) << '\n';
        //        }
        //        if (responce.empty())
        //        {
        //            std::cerr << "No response was received from the server"
        //                      << std::endl;
        //        }
        //        GameActions gameActions = nlohmann::json().parse(responce);
    }

    //    // SEND MOVE ACTION
    //    SendShootAction(1, { -6, -2, 8 });

    //    SendMoveAction(2, { -6, -3, 9 });

    //    //    SendChatAction("gl hf");

    //    // SEND TURN ACTION
    //    SendTurnAction();

    //    // GET GAME ACTIONS
    //    sent = Singleton<Server>::instance("wgforge-srv.wargaming.net", "443")
    //               ->SendAction(Server::Action::GAME_ACTIONS,
    //               nlohmann::json(""));
    //    if (!sent)
    //    {
    //        std::cerr << "Data wasn't sent" << std::endl;
    //    }

    //    result = Server::Result::OKEY;
    //    // какой-то цирк (первый responce всегда пустой)
    //    responce = Singleton<Server>::instance("wgforge-srv.wargaming.net",
    //    "443")
    //                   ->ReceiveResult(result);
    //    if (result != Server::Result::OKEY)
    //    {
    //        std::cerr << "GameActions request result: " <<
    //        static_cast<int>(result)
    //                  << '\n';
    //    }
    //    if (responce.empty())
    //    {
    //        std::cerr << "No response was received from the server" <<
    //        std::endl;
    //    }
    //    GameActions gameActions = nlohmann::json().parse(responce);

    // LOGOUT
    isSuccessfully = client.Logout();
    if (!isSuccessfully)
    {
        std::cerr << "Some error occurred while trying to log out of the "
                     "server"
                  << std::endl;
    }

    return 0;
}
