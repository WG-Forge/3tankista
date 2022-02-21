#include "adapter_system.h"
#include "components/adapter_player_id_component.h"
#include "components/adapter_vehicle_id_component.h"
#include "components/turn_component.h"

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
    if (event->result == Result::OKEY)
    {
        auto entityManager    = ecs::ecsEngine->GetEntityManager();
        auto componentManager = ecs::ecsEngine->GetComponentManager();
        auto playerAdapter    = componentManager->begin<AdapterPlayerIdComponent>();
        auto vehicleAdapter   = componentManager->begin<AdapterVehicleIdComponent>();
        auto json             = (event->data.empty() ? nlohmann::json({}) : nlohmann::json::parse(event->data));
        switch (event->action)
        {
            case Action::LOGIN:
            {
                auto model = json.get<LoginResponseModel>();
                ecs::ecsEngine->SendEvent<LoginResponseEvent>(model);
                break;
            }
            case Action::LOGOUT:
            {
                std::cerr << "Logout is successful\n";
                break;
            }
            case Action::MAP:
            {
                auto model = json.get<MapModel>();
                ecs::ecsEngine->SendEvent<MapResponseEvent>(model);
                break;
            }
            case Action::GAME_STATE:
            {
                auto model = json.get<GameStateModel>();
                std::cout << json.dump() << "\n";
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
            case Action::GAME_ACTIONS:
            {
                auto model = json.get<GameActionsModel>();
                for (auto& action : model.actions)
                {
                    action.playerIndex = playerAdapter->Get(action.playerIndex);
                    switch (action.actionType)
                    {
                        case Action::SHOOT:
                        {
                            auto tmp      = std::get<ShootModel>(action.data);
                            tmp.vehicleId = vehicleAdapter->Get(tmp.vehicleId);
                            action.data   = tmp;
                            break;
                        }
                        case Action::MOVE:
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
            case Action::TURN:
            {
                std::cerr << "TURN №" << componentManager->begin<TurnComponent>()->GetCurrentTurn() << "\n";
                componentManager->begin<TurnComponent>()->SetCurrentTurn(
                    componentManager->begin<TurnComponent>()->GetCurrentTurn() + 1);
                break;
            }
            case Action::CHAT:
            {
                // No model for chat
                break;
            }
            case Action::MOVE:
            {
                auto sentJson = nlohmann::json::parse(event->sentData).get<MoveModel>();
                std::cerr << "MOVE: " << sentJson.vehicleId << " => (" << sentJson.target.x() << ","
                          << sentJson.target.y() << "," << sentJson.target.z() << ')' << std::endl;
                break;
            }
            case Action::SHOOT:
            {
                auto sentJson = nlohmann::json::parse(event->sentData).get<ShootModel>();
                std::cerr << "SHOOT: " << sentJson.vehicleId << " => (" << sentJson.target.x() << ","
                          << sentJson.target.y() << "," << sentJson.target.z() << ')' << std::endl;
                break;
            }
        }
    }
    else if (event->result == Result::TIMEOUT)
    {
        ecs::ecsEngine->SendEvent<SendActionEvent>(Action::TURN, std::string{});
        std::cout << "timeout\n";
    }
}

void AdapterSystem::OnLoginRequestEvent(const LoginRequestEvent* event)
{
    ecs::ecsEngine->SendEvent<SendActionEvent>(Action::LOGIN, nlohmann::json(event->credentials).dump());
}

void AdapterSystem::OnLogoutRequestEvent(const LogoutRequestEvent* event)
{
    ecs::ecsEngine->SendEvent<SendActionEvent>(Action::LOGOUT, std::string{});
}

void AdapterSystem::OnMapRequestEvent(const MapRequestEvent* event)
{
    ecs::ecsEngine->SendEvent<SendActionEvent>(Action::MAP, std::string{});
}

void AdapterSystem::OnGameStateRequestEvent(const GameStateRequestEvent* event)
{
    ecs::ecsEngine->SendEvent<SendActionEvent>(Action::GAME_STATE, std::string{}); // No special model
}

void AdapterSystem::OnGameActionsRequestEvent(const GameActionsRequestEvent* event)
{
    ecs::ecsEngine->SendEvent<SendActionEvent>(Action::GAME_ACTIONS, std::string{}); // No special model
}

void AdapterSystem::OnTurnRequestEvent(const TurnRequestEvent* event)
{
    ecs::ecsEngine->SendEvent<SendActionEvent>(Action::TURN, std::string{}); // No special model
}

void AdapterSystem::OnChatRequestEvent(const ChatRequestEvent* event)
{
    ecs::ecsEngine->SendEvent<SendActionEvent>(Action::CHAT, nlohmann::json(event->chatModel).dump());
}

void AdapterSystem::OnMoveRequestEvent(const MoveRequestEvent* event)
{
    auto vehicleAdapter = ecs::ecsEngine->GetComponentManager()->begin<AdapterVehicleIdComponent>();
    ecs::ecsEngine->SendEvent<SendActionEvent>(
        Action::MOVE,
        nlohmann::json(MoveModel{ vehicleAdapter->GetServerId(event->model.vehicleId), event->model.target }).dump());
}

void AdapterSystem::OnShootRequestEvent(const ShootRequestEvent* event)
{
    auto vehicleAdapter = ecs::ecsEngine->GetComponentManager()->begin<AdapterVehicleIdComponent>();
    ecs::ecsEngine->SendEvent<SendActionEvent>(
        Action::SHOOT,
        nlohmann::json(ShootModel{ vehicleAdapter->GetServerId(event->model.vehicleId), event->model.target }).dump());
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