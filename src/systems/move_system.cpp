#include "move_system.h"
#include "components/attack_matrix_component.h"
#include "components/capture_points_component.h"
#include "components/hex_map_component.h"
#include "components/player_id_component.h"
#include "components/transform_component.h"
#include "components/turn_component.h"
#include "components/vehicle_id_component.h"
#include "entities/map/content.h"
#include "entities/map/map.h"
#include "systems/gameplay_system.h"
#include "win_system.h"
#include "utility/map_utility.h"
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
    auto world            = entityManager->GetEntity(componentManager->begin<TurnComponent>()->GetOwner());
    auto hexMapComponent  = world->GetComponent<HexMapComponent>();

    for (auto& action : event->actions)
    {
        auto entity             = entityManager->GetEntity(action.vehicleId);
        auto transformComponent = entity->GetComponent<TransformComponent>();
        auto cellType = MapUtility::GetHexMapComponentCell(hexMapComponent, transformComponent->GetPosition());
        if (cellType == CellState::FRIEND)
        {
            MapUtility::SetHexMapComponentCell(
                hexMapComponent, transformComponent->GetPosition(), CellState::EMPTY);
            MapUtility::SetHexMapComponentCell(hexMapComponent, action.target, CellState::FRIEND);
        }
        else if (cellType == CellState::ENEMY)
        {
            if (entity->GetComponent<SpawnPositionComponent>()->GetSpawnPosition() == transformComponent->GetPosition())
            {
                MapUtility::SetHexMapComponentCell(
                    hexMapComponent, transformComponent->GetPosition(), CellState::ENEMY_SPAWN);
            }
            else
            {
                MapUtility::SetHexMapComponentCell(
                    hexMapComponent, transformComponent->GetPosition(), CellState::EMPTY);
            }
            MapUtility::SetHexMapComponentCell(hexMapComponent, action.target, CellState::ENEMY);
        }
        transformComponent->SetPosition(action.target);
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
