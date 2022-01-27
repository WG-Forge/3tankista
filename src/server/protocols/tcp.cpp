#include "tcp.h"

Tcp::Tcp(const std::string& host, const std::string& port)
    : errorCode()
    , ioContext()
    , socket(ioContext)
{
    using asio::ip::tcp;
    tcp::resolver resolver(this->GetContext());
    const auto&   endPoints = resolver.resolve(host, port);
    asio::connect(this->GetSocket(), endPoints, this->GetErrorCode());
}

Tcp::~Tcp() {}

std::size_t Tcp::Send(const asio::const_buffer& buffer)
{
    return this->GetSocket().send(buffer, 0, this->GetErrorCode());
}

std::size_t Tcp::Receive(const asio::mutable_buffer& buffer)
{
    return this->GetSocket().receive(buffer, 0, this->GetErrorCode());
}
