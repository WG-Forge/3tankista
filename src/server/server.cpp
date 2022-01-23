#include "server.h"

#include <iostream>

#include "nlohmann/json.hpp"

Server::Server(const std::string &host, const std::string &port) :
    TcpWorker(host, port) {}

bool Server::SendAction(const Action action, const std::string& data) {
    std::size_t dataSize = data.size();
    // if buffer size less than 4(action size in bytes) +
    //                          4(size of data size in bytes) +
    //                          data size in bytes
    if(this->Buffer().size() < actionSizeBytes + messageSizeBytes + dataSize) {
        this->Buffer().resize(actionSizeBytes + messageSizeBytes + dataSize);
    }

    std::memcpy(this->Buffer().data(), &action, sizeof(Action::LOGIN));
    std::memcpy(this->Buffer().data() + actionSizeBytes,
                &dataSize,    sizeof(dataSize));
    std::memcpy(this->Buffer().data() + actionSizeBytes + messageSizeBytes,
                data.data(), dataSize);

    const auto& sent = TcpWorker::Send(asio::const_buffer(this->Buffer().data(),
                                                          actionSizeBytes +
                                                              messageSizeBytes +
                                                              dataSize));
    return sent == (actionSizeBytes + messageSizeBytes + dataSize) ? true : false;
}

std::string Server::ReceiveResult(Result &result)
{
    TcpWorker::Receive(asio::mutable_buffer(this->Buffer().data(),
                                            actionSizeBytes +
                                                messageSizeBytes));
         result   = Result(*Buffer().data());
    int* dataSize = (int*)(this->Buffer().data() + actionSizeBytes);
    this->Buffer().resize(*dataSize + actionSizeBytes + messageSizeBytes);
    TcpWorker::Receive(asio::mutable_buffer(this->Buffer().data() +
                                                actionSizeBytes +
                                                messageSizeBytes, *dataSize));
    return std::move(std::string{this->Buffer().begin() +
                                     actionSizeBytes +
                                     messageSizeBytes, this->Buffer().end()});
}
