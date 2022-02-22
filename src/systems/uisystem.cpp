#include "uisystem.h"

UiSystem::UiSystem()
{
    this->RegisterEventCallbacks();

    // create health bars
    // save their id
}

UiSystem::~UiSystem()
{
    this->UnregisterEventCallbacks();
}

void UiSystem::OnHealthChanged(const HealthChanged* event)
{
    // find health bar in saved id and invoke SetHealth()
    //    ecs::ecsEngine->GetEntityManager
}

void UiSystem::RegisterEventCallbacks()
{
    this->RegisterEventCallback(&UiSystem::OnHealthChanged);
}

void UiSystem::UnregisterEventCallbacks()
{
    this->UnregisterEventCallback(&UiSystem::OnHealthChanged);
}
