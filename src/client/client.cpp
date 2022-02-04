#include "client.h"
#include "nlohmann/json.hpp"
#include "server/server.h"
#include "utility/singleton.h"
#include <iostream>

Client::Client()
    : lastResult()
{
}

Client::~Client() {}

bool Client::Login(const ServerModels::LoginRequestModel& data)
{
    const auto& sent =
        Singleton<Server>::instance("wgforge-srv.wargaming.net", "443")
            ->SendAction(Server::Action::LOGIN, nlohmann::json(data).dump());

    if (!sent)
    {
        std::cerr << "Data wasn't sent" << std::endl;
        return false;
    }

    auto responce =
        Singleton<Server>::instance("wgforge-srv.wargaming.net", "443")
            ->ReceiveResult(this->GetResult());

    if (this->GetResult() != Server::Result::OKEY)
    {
        std::cerr << "Login request result: "
                  << static_cast<int>(this->GetResult()) << '\n';
        return false;
    }

    if (responce.empty())
    {
        std::cerr << "No response was received from the server" << std::endl;
        return false;
    }

    ServerModels::ClientDataModel clientDataModel = nlohmann::json::parse(responce);
    this->SetData(clientDataModel);
    return true;
}

bool Client::Logout()
{
    const auto& sent =
        Singleton<Server>::instance("wgforge-srv.wargaming.net", "443")
            ->SendAction(Server::Action::LOGOUT, "");

    if (!sent)
    {
        std::cerr << "Data wesn't sent" << std::endl;
        return false;
    }

    const auto& responce =
        Singleton<Server>::instance("wgforge-srv.wargaming.net", "443")
            ->ReceiveResult(this->GetResult());

    if (this->GetResult() != Server::Result::OKEY)
    {
        std::cerr << "Logout request result: "
                  << static_cast<int>(this->GetResult()) << '\n';
        return false;
    }

    return responce.empty();
}
