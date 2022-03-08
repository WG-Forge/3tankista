#include "health_system.h"
#include "components/attack_matrix_component.h"
#include "components/health_component.h"
#include "components/player_id_component.h"
#include "components/transform_component.h"
#include "components/ttc_component.h"
#include "components/turn_component.h"
#include "components/vehicle_id_component.h"
#include "entities/map/content.h"
#include "entities/map/map.h"

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
            if (currentEntity->GetComponent<TransformComponent>()->GetPosition() == action.target)
            {
                auto health = currentEntity->GetComponent<HealthComponent>();
                if (health->GetHealth() != 0) // Already destroyed
                {
                    health->SetHealth(std::max(0, health->GetHealth() - damage));
                    // send event about hp changing
                    // currentEntity -- it's target
                    // health -- it's new health
                    if (health->GetHealth() == 0)
                    {
                        ecs::ecsEngine->SendEvent<TankDestroyedEvent>(action.vehicleId, currentEntity->GetEntityID());
                    }
                    ecs::ecsEngine->SendEvent<HealthChanged>(
                        currentEntity->GetComponent<VehicleIdComponent>()->GetVehicleId(),
                        health->GetHealth(),
                        currentEntity->GetComponent<TtcComponent>()->GetMaxHealth());
                }
            }
        }
    }
}

void HealthSystem::HealTanks()
{
    auto entityManager    = ecs::ecsEngine->GetEntityManager();
    auto componentManager = ecs::ecsEngine->GetComponentManager();

    auto turnComponent = componentManager->begin<TurnComponent>().operator->();
    auto map     = dynamic_cast<Map*>(entityManager->GetEntity(componentManager->begin<SizeComponent>()->GetOwner()));
    auto content = dynamic_cast<Content*>(entityManager->GetEntity(map->GetContent()));

    auto lightRepairVector         = content->GetVectorBaseId();
    auto lightRepairPositionVector = content->GetVectorV3i(lightRepairVector);
    auto hardRepairVector          = content->GetVectorBaseId();
    auto hardRepairPositionVector  = content->GetVectorV3i(hardRepairVector);

    std::set<uint64_t> players;

    if ((turnComponent->GetCurrentTurn()) % turnComponent->GetPlayersNumber() == 0 ||
        turnComponent->GetPlayersNumber() == 1)
    {
        std::cout << "heal turn " << turnComponent->GetCurrentTurn() << "\n";
        for (auto it = componentManager->begin<VehicleIdComponent>(); componentManager->end<VehicleIdComponent>() != it;
             ++it)
        {
            auto position = entityManager->GetEntity(it->GetOwner())->GetComponent<TransformComponent>()->GetPosition();
            auto tankType = entityManager->GetEntity(it->GetOwner())->GetComponent<TankTypeComponent>()->GetTankType();
            if (tankType == TankType::MEDIUM)
            {
                auto findIt = std::find(lightRepairPositionVector.begin(), lightRepairPositionVector.end(), position);
                if (findIt != lightRepairPositionVector.end())
                {
                    entityManager->GetEntity(it->GetOwner())
                        ->GetComponent<HealthComponent>()
                        ->SetHealth(
                            entityManager->GetEntity(it->GetOwner())->GetComponent<TtcComponent>()->GetMaxHealth());
                }
            }
            else if (tankType == TankType::HEAVY || tankType == TankType::AT_SPG)
            {
                auto findIt = std::find(hardRepairPositionVector.begin(), hardRepairPositionVector.end(), position);
                if (findIt != hardRepairPositionVector.end())
                {
                    entityManager->GetEntity(it->GetOwner())
                        ->GetComponent<HealthComponent>()
                        ->SetHealth(
                            entityManager->GetEntity(it->GetOwner())->GetComponent<TtcComponent>()->GetMaxHealth());
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
