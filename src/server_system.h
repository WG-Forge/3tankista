#pragma once

#include "game_events.h"
#include "models.h"
#include "tcp.h"

#include "ecs.h"

class ServerSystem : public Tcp,
                     public ecs::System<ServerSystem>,
                     public ecs::event::IEventListener
{
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
    ServerSystem(const std::string& host, const std::string& port);
    ~ServerSystem();

    void OnLoginRequest(const LoginRequestEvent* event);

private:
    void RegisterEventCallbacks();
    void UnregisterEventCallbacks();

private:
    bool        SendAction(const Action action, const std::string& data);
    std::string ReceiveResult(Result& result);

private:
    void  SetBuffer(std::string& buffer) { this->buffer = std::move(buffer); }
    auto& GetBuffer() { return buffer; }
    const auto& GetBuffer() const { return buffer; }

private:
    std::string buffer;
};
