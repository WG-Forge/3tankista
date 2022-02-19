#include "move_system.h"
#include "components/capture_points_component.h"
#include "components/player_id_component.h"
#include "components/position_component.h"
#include "components/vehicle_id_component.h"
#include "entities/map/content.h"
#include "entities/map/map.h"
#include <algorithm>

MoveSystem::MoveSystem()
{
    RegisterEventCallbacks();
}

MoveSystem::~MoveSystem()
{
    UnregisterEventCallbacks();
}

void MoveSystem::OnMoveResponse(const MoveResponseEvent* event)
{
    auto entityManager    = ecs::ecsEngine->GetEntityManager();
    auto componentManager = ecs::ecsEngine->GetComponentManager();
    for (auto& action : event->actions)
    {
        auto entity            = entityManager->GetEntity(action.vehicleId);
        auto positionComponent = entity->GetComponent<PositionComponent>();
        positionComponent->SetPosition(action.target);
    }

    // updating capture points
    auto map     = dynamic_cast<Map*>(entityManager->GetEntity(componentManager->begin<NameComponent>()->GetOwner()));
    auto content = dynamic_cast<Content*>(entityManager->GetEntity(map->GetContent()));
    auto baseVector = content->GetBase();
    std::vector<Vector3i> basePositionVector;
    basePositionVector.reserve(baseVector.size());
    for (auto baseId : baseVector)
    {
        basePositionVector.push_back(
            entityManager->GetEntity(baseId)->GetComponent<PositionComponent>()->GetPosition());
    }
    for (auto it = componentManager->begin<VehicleIdComponent>(); componentManager->end<VehicleIdComponent>() != it;
         ++it)
    {
        auto playerId = entityManager->GetEntity(it->GetOwner())->GetComponent<PlayerIdComponent>()->GetPlayerId();
        auto tank     = entityManager->GetEntity(it->GetOwner());
        auto position = tank->GetComponent<PositionComponent>()->GetPosition();
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

void MoveSystem::RegisterEventCallbacks()
{
    RegisterEventCallback(&MoveSystem::OnMoveResponse);
}

void MoveSystem::UnregisterEventCallbacks()
{
    UnregisterEventCallback(&MoveSystem::OnMoveResponse);
}
