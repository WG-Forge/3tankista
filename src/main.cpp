#include <chrono>
#include <iostream>
#include <thread>
#include <utility>

#include "client.h"
#include "gamearea.h"
#include "gamestate.h"
#include "map.h"
#include "server.h"

#include "singleton.h"

int main()
{
    Client client;
    auto   isSuccessfully = client.Login(ServerModels::LoginRequestModel{
        "ktotoyax", "shtoto", "gdetoyax", 5, 1, false });
    if (!isSuccessfully)
    {
        std::cerr << "Some error occurred while trying to login to the "
                     "server"
                  << std::endl;
    }

    auto sent = Singleton<Server>::instance("wgforge-srv.wargaming.net", "443")
                    ->SendAction(Server::Action::MAP, nlohmann::json(""));
    if (!sent)
    {
        std::cerr << "Data wasn't sent" << std::endl;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
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

    sent = Singleton<Server>::instance("wgforge-srv.wargaming.net", "443")
               ->SendAction(Server::Action::GAME_STATE, nlohmann::json(""));
    if (!sent)
    {
        std::cerr << "Data wasn't sent" << std::endl;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    result   = Server::Result::OKEY;
    responce = Singleton<Server>::instance("wgforge-srv.wargaming.net", "443")
                   ->ReceiveResult(result);
    if (result != Server::Result::OKEY)
    {
        std::cerr << "Map request result: " << static_cast<int>(result) << '\n';
    }
    if (responce.empty())
    {
        std::cerr << "No response was received from the server" << std::endl;
    }

    GameState gameState = nlohmann::json().parse(responce);

    isSuccessfully = client.Logout();
    if (!isSuccessfully)
    {
        std::cerr << "Some error occurred while trying to log out of the "
                     "server"
                  << std::endl;
    }

    return 0;
}
