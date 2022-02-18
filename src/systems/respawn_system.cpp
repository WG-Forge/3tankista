#include "respawn_system.h"
#include "components/health_component.h"
#include "components/position_component.h"
#include "components/spawn_position_component.h"
#include "components/ttc_component.h"

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
    auto position         = componentManager->GetComponent<PositionComponent>(event->entityId);
    auto spawnPosition    = componentManager->GetComponent<SpawnPositionComponent>(event->entityId);
    position->SetPosition(spawnPosition->GetSpawnPosition());
    auto healthComponent = componentManager->GetComponent<HealthComponent>(event->entityId);
    auto maxHealth       = componentManager->GetComponent<TtcComponent>(event->entityId)->GetMaxHealth();
    healthComponent->SetHealth(maxHealth);
}

void RespawnSystem::RegisterEventCallbacks()
{
    RegisterEventCallback(&RespawnSystem::OnTankDestroyedEvent);
}

void RespawnSystem::UnregisterEventCallbacks()
{
    UnregisterEventCallback(&RespawnSystem::OnTankDestroyedEvent);
}
