#include "server_system.h"


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

void ServerSystem::OnMapRequest(const MapRequestEvent* event)
{
    // send inquiry on server
    const auto& sent =
        SendAction(Action::MAP, nlohmann::json(""));

    if (!sent)
    {
        std::cerr << "Data wasn't sent" << std::endl;
        LogError("Data wasn't sent");
    }

    Result lastResult = Result::OKEY;
    auto   responce   = ReceiveResult(lastResult);

    if (lastResult != ServerSystem::Result::OKEY)
    {
        std::cerr << "No response was received from the server" << std::endl;
        LogError("Login request result: " +
                 static_cast<int>(this->GetResult()));
    }

    if (responce.empty())
    {
        LogError("No response was received from the server");
        return /*false*/;
    }

    MapModel mapModel = nlohmann::json::parse(responce);

    // send action in ecs with reply
    ecs::ecsEngine->SendEvent<MapResponceEvent>(mapModel);
}

void ServerSystem::RegisterEventCallbacks()
{
    RegisterEventCallback(&ServerSystem::OnLoginRequest);
    RegisterEventCallback(&ServerSystem::OnMapRequest);
}

void ServerSystem::UnregisterEventCallbacks()
{
    UnregisterEventCallback(&ServerSystem::OnLoginRequest);
    UnregisterEventCallback(&ServerSystem::OnMapRequest);
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
