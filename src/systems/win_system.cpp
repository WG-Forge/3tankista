#include "win_system.h"
#include "components/base_id_component.h"
#include "components/capture_points_component.h"
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
}

void WinSystem::UnregisterEventCallbacks()
{
    UnregisterEventCallback(&WinSystem::OnTankDestroyedEvent);
    UnregisterEventCallback(&WinSystem::OnUpdateCapturePointsEvent);
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

void WinSystem::OnUpdateCapturePointsEvent(const UpdateCapturePointsEvent* event)
{
    UpdateCapturePoints();
}
