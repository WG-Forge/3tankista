#pragma once


#include "game/game_events.h"
#include "game/models/models.h"
#include "entities/models/map_model.h"
#include "tcp.h"

#include "nlohmann/json.hpp"
#include "ecs.h"

class ServerSystem : public Tcp,
                     public ecs::System<ServerSystem>,
                     public ecs::event::IEventListener
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

private:
    static constexpr uint8_t actionSizeBytes  = 4;
    static constexpr uint8_t messageSizeBytes = 4;

public:
    ServerSystem(const std::string& host, const std::string& port);
    ~ServerSystem();
    
    //void OnMapRequest(const MapRequestEvent* event);
    void OnSendActionEvent(const SendActionEvent* event);

private:
    void RegisterEventCallbacks();
    void UnregisterEventCallbacks();

private:
    bool           SendAction(const Action action, const std::string& data);
    nlohmann::json ReceiveResult(Result& result);

private:
    void  SetBuffer(std::string& buffer) { this->buffer = std::move(buffer); }
    auto& GetBuffer() { return buffer; }
    const auto& GetBuffer() const { return buffer; }

private:
    std::string buffer;
};
