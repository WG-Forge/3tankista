#include "tcpworker.h"

TcpWorker::TcpWorker(const std::string& host, const std::string& port)
    : errorCode()
    , ioContext()
    , socket(ioContext)
{
    using asio::ip::tcp;
    tcp::resolver resolver(this->Context());
    const auto&   endPoints = resolver.resolve(host, port);
    asio::connect(this->Socket(), endPoints, this->ErrorCode());
}

TcpWorker::~TcpWorker() {}

std::size_t TcpWorker::Send(const asio::const_buffer& buffer)
{
    return this->Socket().send(buffer, 0, this->ErrorCode());
}

std::size_t TcpWorker::Receive(const asio::mutable_buffer& buffer)
{
    return this->Socket().receive(buffer, 0, this->ErrorCode());
}
