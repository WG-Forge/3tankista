#include "abstract_state.h"
#include "utility/map_utility.h"
#include "utility/path_finder.h"

bool AbstractState::CheckNeutrality(AttackMatrixComponent* attackMatrixComponent, Tank* playerTank, Tank* enemyTank)
{
    auto tankPlayerId  = playerTank->GetComponent<PlayerIdComponent>()->GetPlayerId();
    auto enemyPlayerId = enemyTank->GetComponent<PlayerIdComponent>()->GetPlayerId();

    // If he attacked us
    if (attackMatrixComponent->IsAttacked(enemyPlayerId, tankPlayerId))
        return true;
    // If he attacked by somebody else
    auto attackMatrix = attackMatrixComponent->GetAttackMatrix();
    for (auto& [who, whom] : attackMatrix)
    {
        if (who == tankPlayerId)
            continue;
        if (whom.find(enemyPlayerId) != whom.end())
            return false;
    }
    return true;
}

bool AbstractState::CanShoot(Tank* playerTank, Tank* enemyTank)
{
    bool shoot    = false;
    auto distance = MapUtility::GetDistance(playerTank->GetComponent<TransformComponent>()->GetPosition(),
                                            enemyTank->GetComponent<TransformComponent>()->GetPosition());
    switch (playerTank->GetComponent<TankTypeComponent>()->GetTankType())
    {

        case TankType::MEDIUM:
        {
            shoot = distance == MEDIUM_TANK_DAMAGE_DISTANCE;
            break;
        }
        case TankType::AT_SPG:
        {
            auto tankPosition = playerTank->GetComponent<TransformComponent>()->GetPosition();
            auto point        = enemyTank->GetComponent<TransformComponent>()->GetPosition();
            shoot             = distance <= AT_SPG_TANK_DAMAGE_DISTANCE &&
                    (point.x() == tankPosition.x() || point.y() == tankPosition.y() || point.z() == tankPosition.z());

            break;
        }
        case TankType::HEAVY:
        {
            shoot = distance <= HEAVY_TANK_DAMAGE_DISTANCE && distance > 0;
            break;
        }
        case TankType::LIGHT:
        {
            shoot = distance == LIGHT_TANK_DAMAGE_DISTANCE;
            break;
        }
        case TankType::SPG:
        {
            shoot = MapUtility::GetDistance(enemyTank->GetComponent<TransformComponent>()->GetPosition(),
                                            playerTank->GetComponent<TransformComponent>()->GetPosition()) ==
                    MEDIUM_TANK_DAMAGE_DISTANCE;
            break;
        }
        default:
            break;
    }
    return shoot;
}

bool AbstractState::IsCorrectShootPosition(HexMapComponent* map, Tank* tank, Tank* enemy)
{
    PathFinder pathFinder;
    pathFinder.SetHexMapComponent(map);
    pathFinder.SetStartPoint(tank->GetComponent<TransformComponent>()->GetPosition());
    bool result   = false;
    auto position = enemy->GetComponent<TransformComponent>()->GetPosition();
    if (tank->GetComponent<TankTypeComponent>()->GetTankType() == TankType::AT_SPG)
    {
        if (pathFinder.GetDistance(position) != -1 &&
            pathFinder.GetDistance(position) ==
                MapUtility::GetDistance(tank->GetComponent<TransformComponent>()->GetPosition(), position))
        {
            result = true;
        }
    }
    else
    {
        result = MapUtility::GetHexMapComponentCell(
                     ecs::ecsEngine->GetComponentManager()->begin<HexMapComponent>().operator->(), position) !=
                 CellState::OBSTACLE;
    }
    return result;
}

Vector3i AbstractState::GetShootPosition(Tank* tank, Tank* enemyTank)
{

    auto enemyPosition = enemyTank->GetComponent<TransformComponent>()->GetPosition();
    auto tankPosition  = tank->GetComponent<TransformComponent>()->GetPosition();
    switch (tank->GetComponent<TankTypeComponent>()->GetTankType())
    {

        case TankType::AT_SPG:
        {
            int      distance = MapUtility::GetDistance(enemyPosition, tankPosition);
            Vector3i delta    = enemyPosition - tankPosition;
            enemyPosition     = tankPosition + delta / distance;

            break;
        }
        default:

            break;
    }

    return enemyPosition;
}
