#pragma once

#include "asio.hpp"
#include <string>

class Tcp
{
public:
    Tcp(const std::string& host, const std::string& port);
    virtual ~Tcp() = default;

protected:
    std::size_t Send(const asio::const_buffer& buffer);
    std::size_t Receive(const asio::mutable_buffer& buffer);

private:
    void        SetErrorCode(const asio::error_code& error) = delete;
    auto&       GetErrorCode() { return this->errorCode; }
    const auto& GetErrorCode() const { return this->errorCode; }

    void        SetContext(const asio::io_context& context) = delete;
    auto&       GetContext() { return this->ioContext; }
    const auto& GetContext() const { return this->ioContext; }

    void        SetSocket(const asio::ip::tcp::socket& socket) = delete;
    auto&       GetSocket() { return this->socket; }
    const auto& GetSocket() const { return this->socket; }

private:
    asio::error_code      errorCode;
    asio::io_context      ioContext;
    asio::ip::tcp::socket socket;
};
