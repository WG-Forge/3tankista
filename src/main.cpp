#include <chrono>
#include <iostream>
#include <thread>
#include <utility>

#include "client.h"
#include "gameactions.h"
#include "gamearea.h"
#include "gamestate.h"
#include "globalgameactions.h"
#include "map.h"
#include "server.h"

#include "singleton.h"

int main()
{
    // LOGIN
    Client client;
    auto   isSuccessfully = client.Login(ServerModels::LoginRequestModel{
        "v.aleynikovx", "shtoto", "passwordx", 5, 1, false });
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

    std::this_thread::sleep_for(std::chrono::milliseconds(200));
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
    Map      map = nlohmann::json().parse(responce);
    GameArea gameArea(map);
    auto     distance =
        GameArea::GetDistance(Vector3i{ -7, -3, 10 }, Vector3i{ -7, -2, 9 });
    distance =
        GameArea::GetDistance(Vector3i{ -7, -3, 10 }, Vector3i{ -6, -3, 9 });
    distance =
        GameArea::GetDistance(Vector3i{ -7, -3, 10 }, Vector3i{ -6, -2, 8 });

    // GET GAME STATE
    sent = Singleton<Server>::instance("wgforge-srv.wargaming.net", "443")
               ->SendAction(Server::Action::GAME_STATE, nlohmann::json(""));
    if (!sent)
    {
        std::cerr << "Data wasn't sent" << std::endl;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    result   = Server::Result::OKEY;
    responce = Singleton<Server>::instance("wgforge-srv.wargaming.net", "443")
                   ->ReceiveResult(result);
    if (result != Server::Result::OKEY)
    {
        std::cerr << "GameState request result: " << static_cast<int>(result)
                  << '\n';
    }
    if (responce.empty())
    {
        std::cerr << "No response was received from the server" << std::endl;
    }
    else
    {
        GameState gameState = nlohmann::json().parse(responce);
    }

    // SEND MOVE ACTION
    SendShootAction(1, { -6, -2, 8 });

    SendMoveAction(2, { -6, -3, 9 });

    //    SendChatAction("gl hf");

    // SEND TURN ACTION
    SendTurnAction();

    // GET GAME ACTIONS
    sent = Singleton<Server>::instance("wgforge-srv.wargaming.net", "443")
               ->SendAction(Server::Action::GAME_ACTIONS, nlohmann::json(""));
    if (!sent)
    {
        std::cerr << "Data wasn't sent" << std::endl;
    }

    result = Server::Result::OKEY;
    // какой-то цирк (первый responce всегда пустой)
    responce = Singleton<Server>::instance("wgforge-srv.wargaming.net", "443")
                   ->ReceiveResult(result);
    if (result != Server::Result::OKEY)
    {
        std::cerr << "GameActions request result: " << static_cast<int>(result)
                  << '\n';
    }
    if (responce.empty())
    {
        std::cerr << "No response was received from the server" << std::endl;
    }
    GameActions gameActions = nlohmann::json().parse(responce);

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
