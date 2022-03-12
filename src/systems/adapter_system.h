#pragma once

#include "ecs.h"
#include "game/game_events.h"
#include "components/adapter_player_id_component.h"
#include "components/adapter_vehicle_id_component.h"
#include "components/turn_component.h"

class AdapterSystem : public ecs::System<AdapterSystem>, public ecs::event::IEventListener
{
    DECLARE_LOGGER
public:
    AdapterSystem();
    ~AdapterSystem() override;

    void OnReceiveActionEvent(const ReceiveActionEvent* event);
    void OnLoginRequestEvent(const LoginRequestEvent* event);
    void OnLogoutRequestEvent(const LogoutRequestEvent* event);
    void OnMapRequestEvent(const MapRequestEvent* event);
    void OnGameStateRequestEvent(const GameStateRequestEvent* event);
    void OnGameActionsRequestEvent(const GameActionsRequestEvent* event);
    void OnTurnRequestEvent(const TurnRequestEvent* event);
    void OnChatRequestEvent(const ChatRequestEvent* event);
    void OnMoveRequestEvent(const MoveRequestEvent* event);
    void OnShootRequestEvent(const ShootRequestEvent* event);

private:
    void RegisterEventCallbacks();
    void UnregisterEventCallbacks();
};
