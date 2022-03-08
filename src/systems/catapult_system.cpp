#include "catapult_system.h"
#include "components/attack_matrix_component.h"
#include "components/capture_points_component.h"
#include "components/hex_map_component.h"
#include "components/player_id_component.h"
#include "components/transform_component.h"
#include "components/turn_component.h"
#include "components/usage_component.h"
#include "components/vehicle_id_component.h"
#include "entities/map/content.h"
#include "entities/map/map.h"
#include "systems/gameplay_system.h"
#include "win_system.h"
#include <algorithm>

CatapultSystem::CatapultSystem()
{
    RegisterEventCallbacks();
}

CatapultSystem::~CatapultSystem()
{
    UnregisterEventCallbacks();
}

void CatapultSystem::OnMoveResponse(const MoveResponseEvent* event)
{
    auto entityManager    = ecs::ecsEngine->GetEntityManager();
    auto componentManager = ecs::ecsEngine->GetComponentManager();

    auto map     = dynamic_cast<Map*>(entityManager->GetEntity(componentManager->begin<SizeComponent>()->GetOwner()));
    auto content = dynamic_cast<Content*>(entityManager->GetEntity(map->GetContent()));
    auto catapultVectorId = content->GetVectorCatapultId();
    auto catapultVector3i = content->GetVectorV3i(catapultVectorId);

    for (auto& action : event->actions)
    {
        auto tank = entityManager->GetEntity(action.vehicleId);
        auto it   = std::find(catapultVector3i.begin(), catapultVector3i.end(), action.target);
        if (it != catapultVector3i.end())
        {
            auto catapultId = catapultVectorId[std::distance(catapultVector3i.begin(), it) - 1];
            if (tank->GetComponent<ShootRangeBonusComponent>()->GetShootRangeBonus() == 0 &&
                entityManager->GetEntity(catapultId)->GetComponent<UsageComponent>()->GetUsage() < 3)
            {
                tank->GetComponent<ShootRangeBonusComponent>()->SetShootRangeBonus(1);
                auto catapult = entityManager->GetEntity(catapultId);
                catapult->GetComponent<UsageComponent>()->SetUsage(
                    catapult->GetComponent<UsageComponent>()->GetUsage() + 1);
            }
        }
    }
}

void CatapultSystem::OnShootResponse(const ShootResponseEvent* event)
{
    auto entityManager    = ecs::ecsEngine->GetEntityManager();
    auto componentManager = ecs::ecsEngine->GetComponentManager();

    auto map     = dynamic_cast<Map*>(entityManager->GetEntity(componentManager->begin<SizeComponent>()->GetOwner()));
    auto content = dynamic_cast<Content*>(entityManager->GetEntity(map->GetContent()));
    auto catapultVectorId = content->GetVectorCatapultId();
    auto catapultVector3i=content->GetVectorV3i(catapultVectorId);

    for (auto& action : event->actions)
    {
        auto tank       = entityManager->GetEntity(action.vehicleId);
        auto shootBonus = tank->GetComponent<ShootRangeBonusComponent>()->GetShootRangeBonus();
        if (shootBonus == 1)
        {
            auto position = tank->GetComponent<TransformComponent>()->GetPosition();
            auto it       = std::find(catapultVector3i.begin(), catapultVector3i.end(), position);

            if (it != catapultVector3i.end())
            {
                auto catapultId = catapultVectorId[std::distance(catapultVector3i.begin(), it) - 1];
                if (entityManager->GetEntity(catapultId)->GetComponent<UsageComponent>()->GetUsage() < 3)
                {

                    auto catapult = entityManager->GetEntity(catapultId);
                    catapult->GetComponent<UsageComponent>()->SetUsage(
                        catapult->GetComponent<UsageComponent>()->GetUsage() + 1);
                }
                else
                {
                    entityManager->GetEntity(action.vehicleId)
                        ->GetComponent<ShootRangeBonusComponent>()
                        ->SetShootRangeBonus(0);
                }
            }
            else
            {
                entityManager->GetEntity(action.vehicleId)
                    ->GetComponent<ShootRangeBonusComponent>()
                    ->SetShootRangeBonus(0);
            }
        }
    }
}

void CatapultSystem::RegisterEventCallbacks()
{
    RegisterEventCallback(&CatapultSystem::OnMoveResponse);
    RegisterEventCallback(&CatapultSystem::OnShootResponse);
}

void CatapultSystem::UnregisterEventCallbacks()
{
    UnregisterEventCallback(&CatapultSystem::OnMoveResponse);
    UnregisterEventCallback(&CatapultSystem::OnShootResponse);
}
