#include <chrono>
#include <iostream>
#include <thread>

#include "client.h"
#include "gamestate.h"
#include "map.h"
#include "server.h"

#include "singleton.h"

int main()
{
    Client client;
    auto   isSuccessfully = client.Login(ServerModels::LoginRequestModel{
        "ktoto", "shtoto", "gdeto", 40, 1, false });
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

    Map map = nlohmann::json().parse(responce);

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
