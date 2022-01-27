#include <chrono>
#include <iostream>
#include <thread>

#include "client.h"
#include "gameactions.h"
#include "gamestate.h"
#include "map.h"
#include "server.h"

#include "singleton.h"

int main()
{
    // LOGIN
    Client client;
    auto   isSuccessfully = client.Login(ServerModels::LoginRequestModel{
        "ktadfszzfdto", "shtoto", "dsfdzdfto", 2, 1, false });
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

    // GET GAME STATE
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
        std::cerr << "GameState request result: " << static_cast<int>(result)
                  << '\n';
    }
    if (responce.empty())
    {
        std::cerr << "No response was received from the server" << std::endl;
    }

    GameState gameState = nlohmann::json().parse(responce);

    // SEND MOVE ACTION
    ActionData actionData(1, { -6, -5, 9 });
    sent =
        Singleton<Server>::instance("wgforge-srv.wargaming.net", "443")
            ->SendAction(Server::Action::SHOOT,
                         R"({"vehicle_id":1,"target":{"x":-5,"y":-5,"z":10}})");
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
        std::cerr << "Move request result: " << static_cast<int>(result)
                  << '\n';
    }
    if (responce.empty())
    {
        std::cerr << "No response was received from the server" << std::endl;
    }

    // SEND TURN ACTION
    sent = Singleton<Server>::instance("wgforge-srv.wargaming.net", "443")
               ->SendAction(Server::Action::TURN, nlohmann::json(""));
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
        std::cerr << "Turn request result: " << static_cast<int>(result)
                  << '\n';
    }
    if (responce.empty())
    {
        std::cerr << "No response was received from the server" << std::endl;
    }

    // GET GAME ACTIONS
    sent = Singleton<Server>::instance("wgforge-srv.wargaming.net", "443")
               ->SendAction(Server::Action::GAME_ACTIONS, nlohmann::json(""));
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
