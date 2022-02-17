#include "adapter_system.h"
#include "components/adapter_player_id_component.h"
#include "components/adapter_vehicle_id_component.h"

AdapterSystem::AdapterSystem()
{
    RegisterEventCallbacks();
}

AdapterSystem::~AdapterSystem()
{
    UnregisterEventCallbacks();
}

void AdapterSystem::OnReceiveActionEvent(const ReceiveActionEvent* event)
{
    if (event->result == ServerSystem::Result::OKEY)
    {
        auto playerAdapter = ecs::ecsEngine->GetComponentManager()
                                  ->begin<AdapterPlayerIdComponent>();
        auto vehicleAdapter = ecs::ecsEngine->GetComponentManager()
                                   ->begin<AdapterVehicleIdComponent>();
        switch (event->action)
        {
            case ServerSystem::Action::LOGIN:
            {
                auto model  = event->json.get<LoginResponseModel>();
                model.index = playerAdapter->Get(model.index);
                ecs::ecsEngine->SendEvent<LoginResponseEvent>(model);
                break;
            }
            case ServerSystem::Action::LOGOUT:
            {
                // No model for logout
                break;
            }
            case ServerSystem::Action::MAP:
            {
                // TODO: Map Model
                break;
            }
            case ServerSystem::Action::GAME_STATE:
            {
                auto model = event->json.get<GameStateModel>();
                // No need to adapt GameState
                /*
                for (auto& now : model.players)
                {
                    now.idx = playerAdapter.Get(now.idx);
                }
                for (auto& now : model.observers)
                {
                    now.idx = playerAdapter.Get(now.idx);
                }
                model.currentPlayerIndex =
                    playerAdapter.Get(model.currentPlayerIndex);
                std::unordered_map<int, TankModel> adaptedVehicles;
                for (auto& now : model.vehicles)
                {
                    now.second.playerId =
                        playerAdapter.Get(now.second.playerId);
                    adaptedVehicles[vehicleAdapter.Get(now.first)] = now.second;
                }
                model.vehicles = std::move(adaptedVehicles);
                std::unordered_map<int, std::vector<int>> adaptedAttackMatrix;
                for (auto& now : model.attackMatrix)
                {
                    for (auto& it : now.second)
                    {
                        it = playerAdapter.Get(it);
                    }
                    adaptedAttackMatrix[playerAdapter.Get(now.first)] =
                        now.second;
                }
                model.attackMatrix = std::move(adaptedAttackMatrix);
                 */
                ecs::ecsEngine->SendEvent<GameStateResponseEvent>(model);
                break;
            }
            case ServerSystem::Action::GAME_ACTIONS:
            {
                auto model = event->json.get<GameActionsModel>();
                for (auto& action : model.actions)
                {
                    action.playerIndex = playerAdapter->Get(action.playerIndex);
                    switch (action.actionType)
                    {
                        case ServerSystem::Action::SHOOT:
                        {
                            auto tmp      = std::get<ShootModel>(action.data);
                            tmp.vehicleId = vehicleAdapter->Get(tmp.vehicleId);
                            action.data   = tmp;
                            break;
                        }
                        case ServerSystem::Action::MOVE:
                        {
                            auto tmp      = std::get<MoveModel>(action.data);
                            tmp.vehicleId = vehicleAdapter->Get(tmp.vehicleId);
                            action.data   = tmp;
                            break;
                        }
                        default:
                            break;
                    }
                }
                ecs::ecsEngine->SendEvent<GameActionsResponseEvent>(model);
                break;
            }
            case ServerSystem::Action::TURN:
            {
                // No model for turn
                break;
            }
            case ServerSystem::Action::CHAT:
            {
                // No model for chat
                break;
            }
            case ServerSystem::Action::MOVE:
            {
                // No model for move
                break;
            }
            case ServerSystem::Action::SHOOT:
            {
                // No model for shoot
                break;
            }
        }
    }
    else
    {
        // TODO: Error handling logic
    }
}

void AdapterSystem::OnLoginRequestEvent(const LoginRequestEvent* event)
{
    ecs::ecsEngine->SendEvent<SendActionEvent>(ServerSystem::Action::LOGIN,
                                               event->credentials);
}

void AdapterSystem::OnLogoutRequestEvent(const LogoutRequestEvent* event)
{
    ecs::ecsEngine->SendEvent<SendActionEvent>(ServerSystem::Action::LOGOUT,
                                               nlohmann::json());
}

void AdapterSystem::OnMapRequestEvent(const MapRequestEvent* event)
{
    ecs::ecsEngine->SendEvent<SendActionEvent>(ServerSystem::Action::MAP,
                                               nlohmann::json());
}

void AdapterSystem::OnGameStateRequestEvent(const GameStateRequestEvent* event)
{
    ecs::ecsEngine->SendEvent<SendActionEvent>(ServerSystem::Action::GAME_STATE,
                                               nlohmann::json());
}

void AdapterSystem::OnGameActionsRequestEvent(
    const GameActionsRequestEvent* event)
{
    ecs::ecsEngine->SendEvent<SendActionEvent>(
        ServerSystem::Action::GAME_ACTIONS, nlohmann::json());
}

void AdapterSystem::OnTurnRequestEvent(const TurnRequestEvent* event)
{
    ecs::ecsEngine->SendEvent<SendActionEvent>(ServerSystem::Action::TURN,
                                               nlohmann::json());
}

void AdapterSystem::OnChatRequestEvent(const ChatRequestEvent* event)
{
    // TODO: Chat request event
    ecs::ecsEngine->SendEvent<SendActionEvent>(ServerSystem::Action::CHAT,
                                               nlohmann::json());
}

void AdapterSystem::OnMoveRequestEvent(const MoveRequestEvent* event)
{
    // TODO: Move request event
    ecs::ecsEngine->SendEvent<SendActionEvent>(ServerSystem::Action::MOVE,
                                               nlohmann::json());
}

void AdapterSystem::OnShootRequestEvent(const ShootRequestEvent* event)
{
    // TODO: Shoot request event
    ecs::ecsEngine->SendEvent<SendActionEvent>(ServerSystem::Action::SHOOT,
                                               nlohmann::json());
}

void AdapterSystem::RegisterEventCallbacks()
{
    RegisterEventCallback(&AdapterSystem::OnReceiveActionEvent);
    RegisterEventCallback(&AdapterSystem::OnLoginRequestEvent);
    RegisterEventCallback(&AdapterSystem::OnLogoutRequestEvent);
    RegisterEventCallback(&AdapterSystem::OnMapRequestEvent);
    RegisterEventCallback(&AdapterSystem::OnGameStateRequestEvent);
    RegisterEventCallback(&AdapterSystem::OnGameActionsRequestEvent);
    RegisterEventCallback(&AdapterSystem::OnTurnRequestEvent);
    RegisterEventCallback(&AdapterSystem::OnChatRequestEvent);
    RegisterEventCallback(&AdapterSystem::OnMoveRequestEvent);
    RegisterEventCallback(&AdapterSystem::OnShootRequestEvent);
}

void AdapterSystem::UnregisterEventCallbacks()
{
    UnregisterEventCallback(&AdapterSystem::OnReceiveActionEvent);
    UnregisterEventCallback(&AdapterSystem::OnLoginRequestEvent);
    UnregisterEventCallback(&AdapterSystem::OnLogoutRequestEvent);
    UnregisterEventCallback(&AdapterSystem::OnMapRequestEvent);
    UnregisterEventCallback(&AdapterSystem::OnGameStateRequestEvent);
    UnregisterEventCallback(&AdapterSystem::OnGameActionsRequestEvent);
    UnregisterEventCallback(&AdapterSystem::OnTurnRequestEvent);
    UnregisterEventCallback(&AdapterSystem::OnChatRequestEvent);
    UnregisterEventCallback(&AdapterSystem::OnMoveRequestEvent);
    UnregisterEventCallback(&AdapterSystem::OnShootRequestEvent);
}
