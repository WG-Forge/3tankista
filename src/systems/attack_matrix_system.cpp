#include "attack_matrix_system.h"
#include "components/attack_matrix_component.h"
#include "components/hex_map_component.h"
#include "components/player_id_component.h"
#include "components/shoot_range_bonus.h"
#include "components/tank_type_component.h"
#include "components/transform_component.h"
#include "components/ttc_component.h"
#include "components/turn_component.h"
#include "components/vehicle_id_component.h"
#include "utility/map_utility.h"

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
    auto mapComponent          = componentManager->begin<HexMapComponent>().operator->();
    auto turn                  = componentManager->begin<TurnComponent>()->GetCurrentTurn();
    std::cout << "fs " << componentManager->begin<TurnComponent>()->GetCurrentTurn() << "\n";
    std::cout << "num " << event->actions.size() << "\n";
    int b;
    if (turn == 23)
    {
        b = 123;
    }
    std::set<uint64_t> attackedUsers;
    for (auto& action : event->actions)
    {
        std::vector<Vector3i> possiblePositions;
        if (entityManager->GetEntity(action.vehicleId)->GetComponent<TankTypeComponent>()->GetTankType() ==
            TankType::AT_SPG)
        {
            auto     at_spg = entityManager->GetEntity(action.vehicleId);
            auto     range  = at_spg->GetComponent<TtcComponent>()->GetStandartRange();
            auto     bonus  = at_spg->GetComponent<ShootRangeBonusComponent>()->GetShootRangeBonus();
            Vector3i delta  = action.target - at_spg->GetComponent<TransformComponent>()->GetPosition();
            for (int i = 1; i <= range + bonus; i++)
            {
                if (mapComponent->GetCell(MapUtility::Shift(
                        MapUtility::Cube2Hex(at_spg->GetComponent<TransformComponent>()->GetPosition() + delta * i),
                        mapComponent->GetSize())) != static_cast<int32_t>(CellState::OBSTACLE))
                {
                    possiblePositions.push_back(at_spg->GetComponent<TransformComponent>()->GetPosition() + delta * i);
                }
                else
                {
                    break;
                }
            }
        }
        else
        {
            possiblePositions.push_back(action.target);
        }
        for (auto it = componentManager->begin<VehicleIdComponent>(); componentManager->end<VehicleIdComponent>() != it;
             ++it)
        {
            auto currentEntity = entityManager->GetEntity(it->GetOwner());
            auto it_f          = std::find(possiblePositions.begin(),
                                  possiblePositions.end(),
                                  currentEntity->GetComponent<TransformComponent>()->GetPosition());
            if (it_f != possiblePositions.end() &&
                currentEntity->GetComponent<PlayerIdComponent>()->GetPlayerId() != event->playerId)
            {
                attackedUsers.insert(currentEntity->GetComponent<PlayerIdComponent>()->GetPlayerId());
            }
        }
    }
    attackMatrixComponent->ReplaceUserAttacks(event->playerId, attackedUsers);
}
