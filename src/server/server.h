#ifndef SERVER_H
#define SERVER_H

#include <vector>

#include "tcpworker.h"

class Server : public TcpWorker
{
public:
    enum class Action
    {
        LOGIN        = 1,
        LOGOUT       = 2,
        MAP          = 3,
        GAME_STATE   = 4,
        GAME_ACTIONS = 5,
        TURN         = 6,
        CHAT         = 100,
        MOVE         = 101,
        SHOOT        = 102
    };

    enum class Result
    {
        OKEY                     = 0,
        BAD_COMMAND              = 1,
        ACCESS_DENIED            = 2,
        INAPPROPRIATE_GAME_STATE = 3,
        TIMEOUT                  = 4,
        INTERNAL_SERVER_ERROR    = 500
    };

    static constexpr uint8_t actionSizeBytes  = 4;
    static constexpr uint8_t messageSizeBytes = 4;

public:
    Server(const std::string& host, const std::string& port);
    virtual ~Server() = default;

public:
    bool        SendAction(const Action action, const std::string& data);
    std::string ReceiveResult(Result& result);

private:
    void  setBuffer(const std::vector<char>& buffer) { this->buffer = buffer; }
    auto& Buffer() { return buffer; }
    const auto& Buffer() const { return buffer; }

private:
    std::vector<char> buffer;
};

#endif // SERVER_H
