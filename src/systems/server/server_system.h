#pragma once

#include "ecs.h"
#include "enums/action.h"
#include "enums/result.h"
#include "game/game_events.h"
#include "nlohmann/json.hpp"
#include "tcp.h"

class ServerSystem : public Tcp, public ecs::System<ServerSystem>, public ecs::event::IEventListener
{
private:
    static constexpr uint8_t actionSizeBytes  = 4;
    static constexpr uint8_t messageSizeBytes = 4;

public:
    DECLARE_LOGGER
    ServerSystem(const std::string& host, const std::string& port);
    ~ServerSystem();

    void OnSendActionEvent(const SendActionEvent* event);

private:
    void RegisterEventCallbacks();
    void UnregisterEventCallbacks();

private:
    bool        SendAction(const Action action, const std::string& data);
    std::string ReceiveResult(Result& result);

private:
    void        SetBuffer(std::string& buffer) { this->buffer = std::move(buffer); }
    auto&       GetBuffer() { return buffer; }
    const auto& GetBuffer() const { return buffer; }

private:
    std::string buffer;
};
