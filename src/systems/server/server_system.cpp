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

std::string ServerSystem::ReceiveResult(Result& result)
{
    Tcp::Receive(asio::mutable_buffer(this->GetBuffer().data(), actionSizeBytes + messageSizeBytes));
    result       = Result(*(this->GetBuffer()).data());
    int dataSize = *(int*)(this->GetBuffer().data() + actionSizeBytes);
    if (this->GetBuffer().size() < dataSize + actionSizeBytes + messageSizeBytes)
    {
        this->GetBuffer().resize(dataSize + actionSizeBytes + messageSizeBytes);
    }
    Tcp::Receive(asio::mutable_buffer(this->GetBuffer().data() + actionSizeBytes + messageSizeBytes, dataSize));
    return std::move(std::string(this->GetBuffer().data() + actionSizeBytes + messageSizeBytes,
                                 this->GetBuffer().data() + actionSizeBytes + messageSizeBytes + dataSize));
}

void ServerSystem::OnSendActionEvent(const SendActionEvent* event)
{
    std::cerr << "Request: " << static_cast<int>(event->action) << " " << event->data << '\n';
    LogInfo("Request to server: ", event->action, event->data);
    auto sent = SendAction(event->action, event->data);
    if (!sent)
    {
        LogError("Data wasn't sent");
        return;
    }
    Result result   = Result::OKEY;
    auto   response = ReceiveResult(result);
    std::cerr << "Response: " << static_cast<int>(result) << " " << response << "\n\n\n";
    LogInfo("Response from server: ", result, responce);
    if (result != Result::OKEY)
    {
        LogWarning("Result status is not OKEY " + static_cast<int>(this->GetResult()));
    }
    ecs::ecsEngine->SendEvent<ReceiveActionEvent>(event->action, event->data, result, response);
}
