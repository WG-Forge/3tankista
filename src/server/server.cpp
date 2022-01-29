#include "server.h"

#include <iostream>

#include "nlohmann/json.hpp"

Server::Server(const std::string& host, const std::string& port)
    : Tcp(host, port)
{
}

bool Server::SendAction(const Action action, const std::string& data)
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
    return sent == (actionSizeBytes + messageSizeBytes + dataSize) ? true
                                                                   : false;
}

std::string Server::ReceiveResult(Result& result)
{
    Tcp::Receive(asio::mutable_buffer(this->GetBuffer().data(),
                                      actionSizeBytes + messageSizeBytes));
    result       = Result(*(this->GetBuffer()).data());
    int dataSize = *(int*)(this->GetBuffer().data() + actionSizeBytes);
    this->GetBuffer().resize((dataSize + actionSizeBytes + messageSizeBytes) <=
                                     actionSizeBytes + messageSizeBytes
                                 ? 50
                                 : dataSize + actionSizeBytes +
                                       messageSizeBytes);
    Tcp::Receive(asio::mutable_buffer(this->GetBuffer().data() +
                                          actionSizeBytes + messageSizeBytes,
                                      dataSize));
    return std::move(std::string{ this->GetBuffer().begin() + actionSizeBytes +
                                      messageSizeBytes,
                                  this->GetBuffer().end() });
}
