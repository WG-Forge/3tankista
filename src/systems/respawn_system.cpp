#include "respawn_system.h"
#include "components/health_component.h"
#include "components/spawn_position_component.h"
#include "components/transform_component.h"
#include "components/ttc_component.h"
#include "components/turn_component.h"
#include "gameplay_system.h"
#include "utility/map_utility.h"

RespawnSystem::RespawnSystem()
{
    this->RegisterEventCallbacks();
}

RespawnSystem::~RespawnSystem()
{
    this->UnregisterEventCallbacks();
}

void RespawnSystem::OnTankDestroyedEvent(const TankDestroyedEvent* event)
{
    auto componentManager = ecs::ecsEngine->GetComponentManager();
    auto world = ecs::ecsEngine->GetEntityManager()->GetEntity(componentManager->begin<TurnComponent>()->GetOwner());
    auto hexMapComponent = world->GetComponent<HexMapComponent>();
    auto position        = componentManager->GetComponent<TransformComponent>(event->entityId);
    auto cellType        = MapUtility::GetHexMapComponentCell(hexMapComponent, position->GetPosition());
    auto spawnPosition   = componentManager->GetComponent<SpawnPositionComponent>(event->entityId);
    if (CELL_CONTAINS(cellType, CellState::FRIEND))
    {
        MapUtility::RemoveHexMapComponentCell(hexMapComponent, position->GetPosition(), CellState::FRIEND);
        MapUtility::AddHexMapComponentCell(hexMapComponent, spawnPosition->GetSpawnPosition(), CellState::FRIEND);
    }
    else if (CELL_CONTAINS(cellType, CellState::ENEMY))
    {
        MapUtility::RemoveHexMapComponentCell(hexMapComponent, position->GetPosition(), CellState::ENEMY);
        MapUtility::AddHexMapComponentCell(hexMapComponent, spawnPosition->GetSpawnPosition(), CellState::ENEMY);
    }
    position->SetPosition(spawnPosition->GetSpawnPosition());
    auto healthComponent = componentManager->GetComponent<HealthComponent>(event->entityId);
    auto maxHealth       = componentManager->GetComponent<TtcComponent>(event->entityId)->GetMaxHealth();
    healthComponent->SetHealth(maxHealth);
    // send event about new health. See health_system
    ecs::ecsEngine->SendEvent<HealthChanged>(
        componentManager->GetComponent<VehicleIdComponent>(event->entityId)->GetVehicleId(),
        healthComponent->GetHealth(),
        maxHealth);
}

void RespawnSystem::RegisterEventCallbacks()
{
    RegisterEventCallback(&RespawnSystem::OnTankDestroyedEvent);
}

void RespawnSystem::UnregisterEventCallbacks()
{
    UnregisterEventCallback(&RespawnSystem::OnTankDestroyedEvent);
}
