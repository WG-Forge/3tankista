#include "tcpworker.h"

TcpWorker::TcpWorker(const std::string& host, const std::string& port)
    : errorCode()
    , ioContext()
    , socket(ioContext)
{
    using asio::ip::tcp;
    tcp::resolver resolver(this->GetContext());
    const auto&   endPoints = resolver.resolve(host, port);
    asio::connect(this->GetSocket(), endPoints, this->GetErrorCode());
}

TcpWorker::~TcpWorker() {}

std::size_t TcpWorker::Send(const asio::const_buffer& buffer)
{
    return this->GetSocket().send(buffer, 0, this->GetErrorCode());
}

std::size_t TcpWorker::Receive(const asio::mutable_buffer& buffer)
{
    return this->GetSocket().receive(buffer, 0, this->GetErrorCode());
}
