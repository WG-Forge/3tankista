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

void ServerSystem::RegisterEventCallbacks()
{
    RegisterEventCallback(&ServerSystem::OnSendActionEvent);
}

void ServerSystem::UnregisterEventCallbacks()
{
    UnregisterEventCallback(&ServerSystem::OnSendActionEvent);
}

bool ServerSystem::SendAction(const Action action, const std::string& data)
{
    std::size_t dataSize = data.size();
    if (this->GetBuffer().size() < actionSizeBytes + messageSizeBytes + dataSize)
    {
        this->GetBuffer().resize(actionSizeBytes + messageSizeBytes + dataSize);
    }

    std::memcpy(this->GetBuffer().data(), &action, sizeof(Action::LOGIN));
    std::memcpy(this->GetBuffer().data() + actionSizeBytes, &dataSize, sizeof(dataSize));
    std::memcpy(this->GetBuffer().data() + actionSizeBytes + messageSizeBytes, data.data(), dataSize);

    const auto& sent =
        Tcp::Send(asio::const_buffer(this->GetBuffer().data(), actionSizeBytes + messageSizeBytes + dataSize));
    return sent == (actionSizeBytes + messageSizeBytes + dataSize);
}

nlohmann::json ServerSystem::ReceiveResult(Result& result)
{
    Tcp::Receive(asio::mutable_buffer(this->GetBuffer().data(), actionSizeBytes + messageSizeBytes));
    result       = Result(*(this->GetBuffer()).data());
    int dataSize = *(int*)(this->GetBuffer().data() + actionSizeBytes);
    if (this->GetBuffer().size() < dataSize + actionSizeBytes + messageSizeBytes)
    {
        this->GetBuffer().resize(dataSize + actionSizeBytes + messageSizeBytes);
    }
    Tcp::Receive(asio::mutable_buffer(this->GetBuffer().data() + actionSizeBytes + messageSizeBytes, dataSize));
    return std::move(nlohmann::json::parse(this->GetBuffer().data() + actionSizeBytes + messageSizeBytes,
                                           this->GetBuffer().data() + actionSizeBytes + messageSizeBytes + dataSize));
}

void ServerSystem::OnSendActionEvent(const SendActionEvent* event)
{
    bool sent;
    if (event->action == Action::LOGIN)
    {
        sent = SendAction(event->action, event->json.dump());
    }
    else
    {
        sent = SendAction(event->action, event->json);
    }
    if (!sent)
    {
        LogError("Data wasn't sent");
        return;
    }
    Result result   = Result::OKEY;
    auto   response = ReceiveResult(result);
    if (result != Result::OKEY)
    {
        LogWarning("Result status is not OKEY " + static_cast<int>(this->GetResult()));
    }
    std::cout << response.dump() << "\n";

    ecs::ecsEngine->SendEvent<ReceiveActionEvent>(event->action, event->json, result, response);
}
