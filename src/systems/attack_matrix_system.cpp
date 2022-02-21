#include "attack_matrix_system.h"
#include "components/attack_matrix_component.h"
#include "components/player_id_component.h"
#include "components/position_component.h"
#include "components/vehicle_id_component.h"

AttackMatrixSystem::AttackMatrixSystem()
{
    RegisterEventCallbacks();
}

AttackMatrixSystem::~AttackMatrixSystem()
{
    UnregisterEventCallbacks();
}

void AttackMatrixSystem::RegisterEventCallbacks()
{
    RegisterEventCallback(&AttackMatrixSystem::OnShootResponseEvent);
}

void AttackMatrixSystem::UnregisterEventCallbacks()
{
    UnregisterEventCallback(&AttackMatrixSystem::OnShootResponseEvent);
}

void AttackMatrixSystem::OnShootResponseEvent(const ShootResponseEvent* event)
{
    auto entityManager         = ecs::ecsEngine->GetEntityManager();
    auto componentManager      = ecs::ecsEngine->GetComponentManager();
    auto attackMatrixComponent = componentManager->begin<AttackMatrixComponent>().operator->();

    std::set<uint64_t> attackedUsers;

    for (auto& action : event->actions)
    {
        for (auto it = componentManager->begin<VehicleIdComponent>(); componentManager->end<VehicleIdComponent>() != it;
             ++it)
        {
            auto currentEntity = entityManager->GetEntity(it->GetOwner());
            if (currentEntity->GetComponent<PositionComponent>()->GetPosition() == action.target)
            {
                attackedUsers.insert(currentEntity->GetComponent<PlayerIdComponent>()->GetPlayerId());
            }
        }
    }
    attackMatrixComponent->ReplaceUserAttacks(event->playerId, attackedUsers);
}
