#include "health_system.h"
#include "components/health_component.h"
#include "components/position_component.h"
#include "components/ttc_component.h"
#include "components/vehicle_id_component.h"

HealthSystem::HealthSystem()
{
    this->RegisterEventCallbacks();
}

HealthSystem::~HealthSystem()
{
    this->UnregisterEventCallbacks();
}

void HealthSystem::OnShootResponse(const ShootResponseEvent* event)
{
    auto entityManager    = ecs::ecsEngine->GetEntityManager();
    auto componentManager = ecs::ecsEngine->GetComponentManager();
    for (auto& action : event->actions)
    {
        auto damage = entityManager->GetEntity(action.vehicleId)->GetComponent<TtcComponent>()->GetDamage();
        for (auto it = componentManager->begin<VehicleIdComponent>(); componentManager->end<VehicleIdComponent>() != it;
             ++it)
        {
            auto currentEntity = entityManager->GetEntity(it->GetOwner());
            if (currentEntity->GetComponent<PositionComponent>()->GetPosition() == action.target)
            {
                auto health = currentEntity->GetComponent<HealthComponent>();
                health->SetHealth(std::max(0, health->GetHealth() - damage));
                if (health->GetHealth() == 0)
                {
                    ecs::ecsEngine->SendEvent<TankDestroyedEvent>(currentEntity->GetEntityID());
                }
            }
        }
    }
}

void HealthSystem::RegisterEventCallbacks()
{
    RegisterEventCallback(&HealthSystem::OnShootResponse);
}

void HealthSystem::UnregisterEventCallbacks()
{
    UnregisterEventCallback(&HealthSystem::OnShootResponse);
}