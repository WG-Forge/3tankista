#ifndef TCPWORKER_H
#define TCPWORKER_H

#include "string"

#include "asio.hpp"

class TcpWorker
{
public:
    TcpWorker(const std::string& host, const std::string& port);
    virtual ~TcpWorker();

protected:
    std::size_t Send(const asio::const_buffer& buffer);
    std::size_t Receive(const asio::mutable_buffer& buffer);

private:
    void        setErrorCode(const asio::error_code& error) = delete;
    auto&       ErrorCode() { return this->errorCode; }
    const auto& ErrorCode() const { return this->errorCode; }

    void        setContext(const asio::io_context& context) = delete;
    auto&       Context() { return this->ioContext; }
    const auto& Context() const { return this->ioContext; }

    void        setSocket(const asio::ip::tcp::socket& socket) = delete;
    auto&       Socket() { return this->socket; }
    const auto& Socket() const { return this->socket; }

private:
    asio::error_code      errorCode;
    asio::io_context      ioContext;
    asio::ip::tcp::socket socket;
};

#endif // TCPWORKER_H
