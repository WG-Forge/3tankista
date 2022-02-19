#include "action_system.h"
#include "enums/action.h"
#include <unordered_map>

ActionSystem::ActionSystem()
{
    RegisterEventCallbacks();
}

ActionSystem::~ActionSystem()
{
    UnregisterEventCallbacks();
}

void ActionSystem::OnGameActionsResponseEvent(const GameActionsResponseEvent* event)
{
    std::unordered_map<uint64_t, std::vector<ChatModel>>  chatActions;
    std::unordered_map<uint64_t, std::vector<MoveModel>>  moveActions;
    std::unordered_map<uint64_t, std::vector<ShootModel>> shootActions;
    for (const auto& action : event->gameActionsModel.actions)
    {
        switch (action.actionType)
        {
            case Action::CHAT:
            {
                if (chatActions.find(action.playerIndex) == chatActions.end())
                    chatActions[action.playerIndex] = std::vector<ChatModel>();
                chatActions[action.playerIndex].push_back(std::get<ChatModel>(action.data));
                break;
            }
            case Action::MOVE:
            {
                if (moveActions.find(action.playerIndex) == moveActions.end())
                    moveActions[action.playerIndex] = std::vector<MoveModel>();
                moveActions[action.playerIndex].push_back(std::get<MoveModel>(action.data));
                break;
            }
            case Action::SHOOT:
            {
                if (shootActions.find(action.playerIndex) == shootActions.end())
                    shootActions[action.playerIndex] = std::vector<ShootModel>();
                shootActions[action.playerIndex].push_back(std::get<ShootModel>(action.data));
                break;
            }
            default:
                break;
        }
    }
    for (auto& now : chatActions)
    {
        ecs::ecsEngine->SendEvent<ChatResponseEvent>(now.first, now.second);
    }
    for (auto& now : moveActions)
    {
        ecs::ecsEngine->SendEvent<MoveResponseEvent>(now.first, now.second);
    }
    for (auto& now : shootActions)
    {
        ecs::ecsEngine->SendEvent<ShootResponseEvent>(now.first, now.second);
    }
}

void ActionSystem::RegisterEventCallbacks()
{
    RegisterEventCallback(&ActionSystem::OnGameActionsResponseEvent);
}

void ActionSystem::UnregisterEventCallbacks()
{
    UnregisterEventCallback(&ActionSystem::OnGameActionsResponseEvent);
}
