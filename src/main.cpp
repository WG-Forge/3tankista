#include <chrono>
#include <iostream>
#include <thread>

#include "client/client.h"
#include "game_actions/global_game_actions.h"
#include "game_area/game_area.h"
#include "game_state/game_state.h"
#include "gameplay/gameplay.hpp"
#include "map/map.h"
#include "server/server.h"
#include "utility/singleton.h"

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
    observer = isObserver.at(0) == 'y';

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
    auto          map = std::make_shared<Map>(nlohmann::json().parse(responce));
    auto          gameArea = std::make_shared<GameArea>(*map);
    GameAlgorithm gameAlgorithm(gameArea, map);

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
        auto gameState =
            std::make_unique<GameState>(nlohmann::json().parse(responce));

        gameFinished = gameState->GetFinished();

        if (gameFinished)
        {
            const auto& winner = std::find_if(
                gameState->GetPlayers().begin(),
                gameState->GetPlayers().end(),
                [&](const Player& player)
                { return player.GetData().index == gameState->GetWinner(); });
            std::cerr
                << "Winner: " << winner->GetData().name << ";" << std::endl
                << "Capture points: "
                << gameState->GetWinPoints().at(gameState->GetWinner()).capture
                << ";" << std::endl
                << "Kill points: "
                << gameState->GetWinPoints().at(gameState->GetWinner()).kill
                << ";" << std::endl;
            continue;
        }

        if (client.GetData().index == gameState->GetCurrentPlayerIdx())
        {
            gameAlgorithm.SetGameState(gameState);
            gameAlgorithm.Play();
        }
        SendTurnAction();
    }

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
