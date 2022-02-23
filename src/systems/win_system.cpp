#include "win_system.h"
#include "components/attack_matrix_component.h"
#include "components/base_id_component.h"
#include "components/capture_points_component.h"
#include "components/hex_map_component.h"
#include "components/kill_points_component.h"
#include "components/order_component.h"
#include "components/player_id_component.h"
#include "components/transform_component.h"
#include "components/ttc_component.h"
#include "components/turn_component.h"
#include "components/vehicle_id_component.h"
#include "entities/map/map.h"

WinSystem::WinSystem()
{
    RegisterEventCallbacks();
}

WinSystem::~WinSystem()
{
    UnregisterEventCallbacks();
}

void WinSystem::RegisterEventCallbacks()
{
    RegisterEventCallback(&WinSystem::OnTankDestroyedEvent);
    RegisterEventCallback(&WinSystem::OnUpdateCapturePointsEvent);
    RegisterEventCallback(&WinSystem::OnMoveResponseEvent);
}

void WinSystem::UnregisterEventCallbacks()
{
    UnregisterEventCallback(&WinSystem::OnTankDestroyedEvent);
    UnregisterEventCallback(&WinSystem::OnUpdateCapturePointsEvent);
    UnregisterEventCallback(&WinSystem::OnMoveResponseEvent);
}

void WinSystem::OnTankDestroyedEvent(const TankDestroyedEvent* event)
{
    auto entityManager     = ecs::ecsEngine->GetEntityManager();
    auto killerEntity      = entityManager->GetEntity(event->killerEntityId);
    auto targetEntity      = entityManager->GetEntity(event->entityId);
    auto killerOwner       = entityManager->GetEntity(killerEntity->GetComponent<PlayerIdComponent>()->GetPlayerId());
    auto targetOwner       = entityManager->GetEntity(targetEntity->GetComponent<PlayerIdComponent>()->GetPlayerId());
    auto currentKillPoints = killerOwner->GetComponent<KillPointsComponent>()->GetKillPoints();
    currentKillPoints += targetEntity->GetComponent<TtcComponent>()->GetMaxHealth();
    killerOwner->GetComponent<KillPointsComponent>()->SetKillPoints(currentKillPoints);
    auto lostPoints = targetEntity->GetComponent<CapturePointsComponent>()->GetCapturePoints();
    targetEntity->GetComponent<CapturePointsComponent>()->SetCapturePoints(0);
    auto currentCapturePoints = targetOwner->GetComponent<CapturePointsComponent>()->GetCapturePoints();
    currentCapturePoints -= lostPoints;
    targetOwner->GetComponent<CapturePointsComponent>()->SetCapturePoints(currentCapturePoints);
}

void WinSystem::OnMoveResponseEvent(const MoveResponseEvent* event)
{
    auto entityManager    = ecs::ecsEngine->GetEntityManager();
    auto componentManager = ecs::ecsEngine->GetComponentManager();
    auto map     = dynamic_cast<Map*>(entityManager->GetEntity(componentManager->begin<SizeComponent>()->GetOwner()));
    auto content = dynamic_cast<Content*>(entityManager->GetEntity(map->GetContent()));
    auto baseVector = content->GetBase();
    std::vector<Vector3i> basePositionVector;
    basePositionVector.reserve(baseVector.size());
    for (auto& baseId : baseVector)
    {
        basePositionVector.push_back(
            entityManager->GetEntity(baseId)->GetComponent<TransformComponent>()->GetPosition());
    }
    for (auto& action : event->actions)
    {
        auto entity             = entityManager->GetEntity(action.vehicleId);
        auto transformComponent = entity->GetComponent<TransformComponent>();
        if (std::find(basePositionVector.begin(), basePositionVector.end(), transformComponent->GetPosition()) !=
            basePositionVector.end())
        {
            if (std::find(basePositionVector.begin(), basePositionVector.end(), action.target) ==
                basePositionVector.end())
            {
                auto CapturePointsOfTank = entity->GetComponent<CapturePointsComponent>()->GetCapturePoints();
                entity->GetComponent<CapturePointsComponent>()->SetCapturePoints(0);
                auto newCapturePointsOfPlayer =
                    entityManager->GetEntity(entity->GetComponent<PlayerIdComponent>()->GetPlayerId())
                        ->GetComponent<CapturePointsComponent>()
                        ->GetCapturePoints() -
                    CapturePointsOfTank;
                entityManager->GetEntity(entity->GetComponent<PlayerIdComponent>()->GetPlayerId())
                    ->GetComponent<CapturePointsComponent>()
                    ->SetCapturePoints(newCapturePointsOfPlayer);
            }
        }
    }
}

void WinSystem::UpdateCapturePoints()
{
    auto entityManager    = ecs::ecsEngine->GetEntityManager();
    auto componentManager = ecs::ecsEngine->GetComponentManager();
    auto map     = dynamic_cast<Map*>(entityManager->GetEntity(componentManager->begin<SizeComponent>()->GetOwner()));
    auto content = dynamic_cast<Content*>(entityManager->GetEntity(map->GetContent()));
    auto baseVector = content->GetBase();
    std::vector<Vector3i> basePositionVector;
    basePositionVector.reserve(baseVector.size());
    for (auto baseId : baseVector)
    {
        basePositionVector.push_back(
            entityManager->GetEntity(baseId)->GetComponent<TransformComponent>()->GetPosition());
    }
    std::set<uint64_t> players;
    for (auto it = componentManager->begin<VehicleIdComponent>(); componentManager->end<VehicleIdComponent>() != it;
         ++it)
    {
        auto playerId      = entityManager->GetEntity(it->GetOwner())->GetComponent<PlayerIdComponent>()->GetPlayerId();
        auto tank          = entityManager->GetEntity(it->GetOwner());
        auto position      = tank->GetComponent<TransformComponent>()->GetPosition();
        auto turnComponent = componentManager->begin<TurnComponent>().operator->();
        if ((turnComponent->GetCurrentTurn()) % turnComponent->GetPlayersNumber() == 0 ||
            turnComponent->GetPlayersNumber() == 1)
        {
            if (std::find(basePositionVector.begin(), basePositionVector.end(), position) != basePositionVector.end())
            {
                players.insert(playerId);
            }
        }
    }
    if (players.size() > 2)
    {
        return;
    }
    for (auto it = componentManager->begin<VehicleIdComponent>(); componentManager->end<VehicleIdComponent>() != it;
         ++it)
    {
        auto playerId      = entityManager->GetEntity(it->GetOwner())->GetComponent<PlayerIdComponent>()->GetPlayerId();
        auto tank          = entityManager->GetEntity(it->GetOwner());
        auto position      = tank->GetComponent<TransformComponent>()->GetPosition();
        auto turnComponent = componentManager->begin<TurnComponent>().operator->();
        if ((turnComponent->GetCurrentTurn()) % turnComponent->GetPlayersNumber() == 0 ||
            turnComponent->GetPlayersNumber() == 1)
        {
            if (std::find(basePositionVector.begin(), basePositionVector.end(), position) != basePositionVector.end())
            {
                auto newCapturePointsOfTank = tank->GetComponent<CapturePointsComponent>()->GetCapturePoints() + 1;
                tank->GetComponent<CapturePointsComponent>()->SetCapturePoints(newCapturePointsOfTank);
                auto newCapturePointsOfPlayer =
                    entityManager->GetEntity(playerId)->GetComponent<CapturePointsComponent>()->GetCapturePoints() + 1;
                entityManager->GetEntity(playerId)->GetComponent<CapturePointsComponent>()->SetCapturePoints(
                    newCapturePointsOfPlayer);
            }
        }
    }
}

std::vector<std::pair<uint64_t, std::pair<int, int>>> WinSystem::GetWinPoints()
{
    auto                                                  componentManager = ecs::ecsEngine->GetComponentManager();
    auto                                                  entityManager    = ecs::ecsEngine->GetEntityManager();
    std::vector<std::pair<uint64_t, std::pair<int, int>>> players;

    for (auto it = componentManager->begin<KillPointsComponent>(); componentManager->end<KillPointsComponent>() != it;
         ++it)
    {
        auto                player = entityManager->GetEntity(it->GetOwner());
        std::pair<int, int> winPoints{ player->GetComponent<CapturePointsComponent>()->GetCapturePoints(),
                                       it->GetKillPoints() };
        players.push_back({ player->GetComponent<PlayerIdComponent>()->GetPlayerId(), winPoints });
    }
    return players;
}

int WinSystem::GetMaxKillPoints(std::vector<std::pair<uint64_t, std::pair<int, int>>> players)
{
    auto componentManager = ecs::ecsEngine->GetComponentManager();
    int  max              = 0;
    for (auto& elem : players)
    {
        if (max < elem.second.second)
        {
            max = elem.second.second;
        }
    }
    return max;
}

void WinSystem::OnUpdateCapturePointsEvent(const UpdateCapturePointsEvent* event)
{
    UpdateCapturePoints();
}
