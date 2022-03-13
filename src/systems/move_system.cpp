#include "move_system.h"

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
    auto mainPlayerId     = componentManager->begin<MainPlayerComponent>()->GetMainPlayerId();
    auto turnComponent    = componentManager->begin<TurnComponent>().operator->();

    uint64_t currentPlayerId;
    for (auto it = componentManager->begin<OrderComponent>(); componentManager->end<OrderComponent>() != it; ++it)
    {
        if (it->GetOrder() == (turnComponent->GetCurrentTurn() - 1) % turnComponent->GetPlayersNumber())
        {
            currentPlayerId = it->GetOwner();
        }
    }
    bool notIsMainPlayer = mainPlayerId != currentPlayerId ||
                           entityManager->GetEntity(mainPlayerId)->GetComponent<ObserverComponent>()->GetIsObserver();
    for (auto& action : event->actions)
    {
        auto entity             = entityManager->GetEntity(action.vehicleId);
        auto transformComponent = entity->GetComponent<TransformComponent>();
        auto cellType = MapUtility::GetHexMapComponentCell(hexMapComponent, transformComponent->GetPosition());
        if (notIsMainPlayer)
        {
            if (CELL_CONTAINS(cellType, CellState::FRIEND))
            {
                MapUtility::RemoveHexMapComponentCell(
                    hexMapComponent, transformComponent->GetPosition(), CellState::FRIEND);
                MapUtility::AddHexMapComponentCell(hexMapComponent, action.target, CellState::FRIEND);
            }
            else if (CELL_CONTAINS(cellType, CellState::ENEMY))
            {
                if (entity->GetComponent<SpawnPositionComponent>()->GetSpawnPosition() ==
                    transformComponent->GetPosition())
                {
                    MapUtility::AddHexMapComponentCell(
                        hexMapComponent, transformComponent->GetPosition(), CellState::ENEMY_SPAWN);
                }
                MapUtility::RemoveHexMapComponentCell(
                    hexMapComponent, transformComponent->GetPosition(), CellState::ENEMY);
                MapUtility::AddHexMapComponentCell(hexMapComponent, action.target, CellState::ENEMY);
            }
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
