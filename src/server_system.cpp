#include "server_system.h"

#include "nlohmann/json.hpp"

ServerSystem::ServerSystem(const std::string& host, const std::string& port)
    : Tcp(host, port)
{
    this->RegisterEventCallbacks();
}

ServerSystem::~ServerSystem()
{
    this->UnregisterEventCallbacks();
}

void ServerSystem::OnLoginRequest(const LoginRequestEvent* event)
{
    // send inquiry on server
    const auto& sent =
        SendAction(Action::LOGIN, nlohmann::json(event->credentials).dump());

    if (!sent)
    {
        LogError("Data wasn't sent");
        return /*false*/;
    }

    Result lastResult = Result::OKEY;
    auto   responce   = ReceiveResult(lastResult);

    if (lastResult != ServerSystem::Result::OKEY)
    {
        LogError("Login request result: " +
                 static_cast<int>(this->GetResult()));
        return /*false*/;
    }

    if (responce.empty())
    {
        LogError("No response was received from the server");
        return /*false*/;
    }

    LoginResponceModel loginResponceData = nlohmann::json::parse(responce);

    // send action in ecs with reply
    ecs::ecsEngine->SendEvent<LoginResponceEvent>(loginResponceData);

    return /*true*/;
}

void ServerSystem::RegisterEventCallbacks()
{
    RegisterEventCallback(&ServerSystem::OnLoginRequest);
}

void ServerSystem::UnregisterEventCallbacks()
{
    UnregisterEventCallback(&ServerSystem::OnLoginRequest);
}

bool ServerSystem::SendAction(const Action action, const std::string& data)
{
    std::size_t dataSize = data.size();
    if (this->GetBuffer().size() <
        actionSizeBytes + messageSizeBytes + dataSize)
    {
        this->GetBuffer().resize(actionSizeBytes + messageSizeBytes + dataSize);
    }

    std::memcpy(this->GetBuffer().data(), &action, sizeof(Action::LOGIN));
    std::memcpy(this->GetBuffer().data() + actionSizeBytes,
                &dataSize,
                sizeof(dataSize));
    std::memcpy(this->GetBuffer().data() + actionSizeBytes + messageSizeBytes,
                data.data(),
                dataSize);

    const auto& sent = Tcp::Send(
        asio::const_buffer(this->GetBuffer().data(),
                           actionSizeBytes + messageSizeBytes + dataSize));
    return sent == (actionSizeBytes + messageSizeBytes + dataSize);
}

std::string ServerSystem::ReceiveResult(Result& result)
{
    Tcp::Receive(asio::mutable_buffer(this->GetBuffer().data(),
                                      actionSizeBytes + messageSizeBytes));
    result       = Result(*(this->GetBuffer()).data());
    int dataSize = *(int*)(this->GetBuffer().data() + actionSizeBytes);
    this->GetBuffer().resize(dataSize + actionSizeBytes + messageSizeBytes);
    Tcp::Receive(asio::mutable_buffer(this->GetBuffer().data() +
                                          actionSizeBytes + messageSizeBytes,
                                      dataSize));
    return std::move(std::string{ this->GetBuffer().begin() + actionSizeBytes +
                                      messageSizeBytes,
                                  this->GetBuffer().end() });
}
