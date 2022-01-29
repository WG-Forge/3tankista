#include "globalgameactions.h"

#include <iostream>

#include "nlohmann/json.hpp"

#include "actiondata.h"
#include "server.h"
#include "singleton.h"

bool SendTurnAction()
{
    bool        isSuccessfully = true;
    const auto& sent =
        Singleton<Server>::instance("wgforge-srv.wargaming.net", "443")
            ->SendAction(Server::Action::TURN, nlohmann::json(""));
    if (!sent)
    {
        std::cerr << "Data wasn't sent" << std::endl;
        isSuccessfully = false;
    }

    auto        result = Server::Result::OKEY;
    const auto& responce =
        Singleton<Server>::instance("wgforge-srv.wargaming.net", "443")
            ->ReceiveResult(result);
    if (result != Server::Result::OKEY)
    {
        std::cerr << "Turn request result: " << static_cast<int>(result) << " "
                  << responce << std::endl;
        isSuccessfully = false;
    }

    return isSuccessfully;
}

bool SendChatAction(const std::string& message)
{
    bool        isSuccessfully = true;
    const auto& sent =
        Singleton<Server>::instance("wgforge-srv.wargaming.net", "443")
            ->SendAction(Server::Action::CHAT,
                         R"({"message":")" + message + R"("})");
    if (!sent)
    {
        std::cerr << "Data wasn't sent" << std::endl;
        isSuccessfully = false;
    }

    auto        result = Server::Result::OKEY;
    const auto& responce =
        Singleton<Server>::instance("wgforge-srv.wargaming.net", "443")
            ->ReceiveResult(result);
    if (result != Server::Result::OKEY)
    {
        std::cerr << "Move request result: " << static_cast<int>(result) << " "
                  << responce << std::endl;
        isSuccessfully = false;
    }

    return isSuccessfully;
}

bool SendMoveAction(const int vehicleId, const Vector3i& target)
{
    bool        isSuccessfully = true;
    const auto& sent =
        Singleton<Server>::instance("wgforge-srv.wargaming.net", "443")
            ->SendAction(Server::Action::MOVE,
                         nlohmann::json(ActionData(vehicleId, target)).dump());
    if (!sent)
    {
        std::cerr << "Data wasn't sent" << std::endl;
        isSuccessfully = false;
    }

    auto        result = Server::Result::OKEY;
    const auto& responce =
        Singleton<Server>::instance("wgforge-srv.wargaming.net", "443")
            ->ReceiveResult(result);
    if (result != Server::Result::OKEY)
    {
        std::cerr << "Move request result: " << static_cast<int>(result) << " "
                  << responce << std::endl;
        isSuccessfully = false;
    }

    return isSuccessfully;
}

bool SendShootAction(const int vehicleId, const Vector3i& target)
{
    bool        isSuccessfully = true;
    const auto& sent =
        Singleton<Server>::instance("wgforge-srv.wargaming.net", "443")
            ->SendAction(Server::Action::SHOOT,
                         nlohmann::json(ActionData(vehicleId, target)).dump());
    if (!sent)
    {
        std::cerr << "Data wasn't sent" << std::endl;
        isSuccessfully = false;
    }

    auto        result = Server::Result::OKEY;
    const auto& responce =
        Singleton<Server>::instance("wgforge-srv.wargaming.net", "443")
            ->ReceiveResult(result);
    if (result != Server::Result::OKEY)
    {
        std::cerr << "Shoot request result: " << static_cast<int>(result) << " "
                  << responce << std::endl;
        isSuccessfully = false;
    }

    return isSuccessfully;
}
