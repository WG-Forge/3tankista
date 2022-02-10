#include "health_system.h"
#include "components/health_component.h"

HealthSystem::HealthSystem()
{
    this->RegisterEventCallbacks();
}

HealthSystem::~HealthSystem()
{
    this->UnregisterEventCallbacks();
}

void HealthSystem::OnShootResponce(const ShootResponceEvent* event)
{
    auto componentManager = ecs::ecsEngine->GetComponentManager();
    for (auto& entity : event->entityIds)
    {
        auto health =
            componentManager->GetComponent<HealthComponent>(entity.first);
        health->SetHealth(health->GetHealth() - entity.second);
    }
}

void HealthSystem::RegisterEventCallbacks()
{
    RegisterEventCallback(&HealthSystem::OnShootResponce);
}

void HealthSystem::UnregisterEventCallbacks()
{
    UnregisterEventCallback(&HealthSystem::OnShootResponce);
}