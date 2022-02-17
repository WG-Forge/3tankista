#include "health_system.h"
#include "components/health_component.h"
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
    // TODO: Implement OnShootResponse method.
//    auto entityManager = ecs::ecsEngine->GetEntityManager();
//    auto componentManager = ecs::ecsEngine->GetComponentManager();
//    for (auto& action : event->actions)
//    {
//        for (auto it = componentManager->begin<VehicleIdComponent>();
//             componentManager->end<VehicleIdComponent>() != it; ++it) {
//            if (it->GetVehicleId() == action.vehicleId) {
//                auto entity = entityManager->GetEntity(it->GetOwner());
//                entity->GetComponent<HealthComponent>()->SetHealth()
//            }
//
//        }
//    }
}

void HealthSystem::RegisterEventCallbacks()
{
    RegisterEventCallback(&HealthSystem::OnShootResponse);
}

void HealthSystem::UnregisterEventCallbacks()
{
    UnregisterEventCallback(&HealthSystem::OnShootResponse);
}