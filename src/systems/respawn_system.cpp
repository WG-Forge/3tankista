#include "respawn_system.h"
#include "components/position_component.h"

RespawnSystem::RespawnSystem()
{
    this->RegisterEventCallbacks();
}

RespawnSystem::~RespawnSystem()
{
    this->UnregisterEventCallbacks();
}

void RespawnSystem::OnTankDestroyedEvent(const TankDestroyedEvent* event) {
    auto componentManager = ecs::ecsEngine->GetComponentManager();
    auto position = componentManager->GetComponent<PositionComponent>(event->entityId);
    auto spawnPosition = componentManager->GetComponent<SpawnComponent>(event->entityId);
    position->SetPosition(spawnPosition->GetPosition());
}

void RespawnSystem::RegisterEventCallbacks()
{
    RegisterEventCallback(&RespawnSystem::OnTankDestroyedEvent);
}

void RespawnSystem::UnregisterEventCallbacks()
{
    UnregisterEventCallback(&RespawnSystem::OnTankDestroyedEvent);
}
