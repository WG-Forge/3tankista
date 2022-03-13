#include "abstract_state.h"
#include "entities/map/map.h"
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
    bool shoot            = false;
    auto distance         = MapUtility::GetDistance(playerTank->GetComponent<TransformComponent>()->GetPosition(),
                                            enemyTank->GetComponent<TransformComponent>()->GetPosition());
    auto componentManager = ecs::ecsEngine->GetComponentManager();
    auto standartRange    = componentManager->GetComponent<TtcComponent>(playerTank->GetEntityID())->GetStandartRange();
    auto shootRangeBonus =
        componentManager->GetComponent<ShootRangeBonusComponent>(playerTank->GetEntityID())->GetShootRangeBonus();
    switch (playerTank->GetComponent<TankTypeComponent>()->GetTankType())
    {
        case TankType::MEDIUM:
        {
            shoot = standartRange <= distance && distance <= standartRange + shootRangeBonus;
            break;
        }
        case TankType::AT_SPG:
        {
            auto tankPosition = playerTank->GetComponent<TransformComponent>()->GetPosition();
            auto point        = enemyTank->GetComponent<TransformComponent>()->GetPosition();
            shoot             = distance <= standartRange + shootRangeBonus &&
                    (point.x() == tankPosition.x() || point.y() == tankPosition.y() || point.z() == tankPosition.z());
            break;
        }
        case TankType::HEAVY:
        {
            shoot = distance <= standartRange + shootRangeBonus && distance > 0;
            break;
        }
        case TankType::LIGHT:
        {
            shoot = standartRange <= distance && distance <= standartRange + shootRangeBonus;
            break;
        }
        case TankType::SPG:
        {
            shoot = standartRange <= distance && distance <= standartRange + shootRangeBonus;
            break;
        }
        default:
            break;
    }
    return shoot;
}

bool AbstractState::IsCorrectShootPosition(HexMapComponent* map, Tank* tank, Tank* enemy)
{
    auto componentManager = ecs::ecsEngine->GetComponentManager();
    auto mapComponent     = componentManager->begin<HexMapComponent>().operator->();

    bool result   = false;
    auto position = enemy->GetComponent<TransformComponent>()->GetPosition();
    if (tank->GetComponent<TankTypeComponent>()->GetTankType() == TankType::AT_SPG)
    {
        std::vector<Vector3i> possiblePositions;
        auto                  range = tank->GetComponent<TtcComponent>()->GetStandartRange();
        auto                  bonus = tank->GetComponent<ShootRangeBonusComponent>()->GetShootRangeBonus();
        Vector3i              delta = position - tank->GetComponent<TransformComponent>()->GetPosition();
        for (int i = 1; i <= range + bonus; i++)
        {
            if (mapComponent->GetCell(MapUtility::Shift(
                    MapUtility::Cube2Hex(tank->GetComponent<TransformComponent>()->GetPosition() + delta * i),
                    mapComponent->GetSize())) != static_cast<int32_t>(CellState::OBSTACLE))
            {
                possiblePositions.push_back(tank->GetComponent<TransformComponent>()->GetPosition() + delta * i);
            }
            else
            {
                break;
            }
        }

        if (std::find(possiblePositions.begin(), possiblePositions.end(), position) != possiblePositions.end())
        {
            result = true;
        }
    }
    else
    {
        result =
            !CELL_CONTAINS(MapUtility::GetHexMapComponentCell(
                               ecs::ecsEngine->GetComponentManager()->begin<HexMapComponent>().operator->(), position),
                           CellState::OBSTACLE);
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

Tank* AbstractState::GetEnemyInShootArea(GameplaySystem::Context& context, Tank* tank)
{
    Tank* target = nullptr;
    for (auto& enemy : context.enemies)
    {
        auto elem = enemy->GetComponent<TransformComponent>()->GetPosition();
        if (CanShoot(tank, enemy))
        {
            if (IsCorrectShootPosition(context.hexMap, tank, enemy))
            {
                if (CheckNeutrality(context.attackMatrix, tank, enemy))
                {
                    if (target == nullptr || target->GetComponent<HealthComponent>()->GetHealth() >
                                                 enemy->GetComponent<HealthComponent>()->GetHealth())
                    {
                        target = enemy;
                    }
                }
            }
        }
    }
    if (target != nullptr)
    {
    }
    return target;
}

bool AbstractState::IsOnTheBase(GameplaySystem::Context& context, Tank* tank)
{
    return CELL_CONTAINS(
        MapUtility::GetHexMapComponentCell(context.hexMap, tank->GetComponent<TransformComponent>()->GetPosition()),
        CellState::BASE);
}

std::vector<Vector3i> AbstractState::GetPathToBase(GameplaySystem::Context& context, Tank* tank)
{
    auto entityManager    = ecs::ecsEngine->GetEntityManager();
    auto componentManager = ecs::ecsEngine->GetComponentManager();

    auto map     = dynamic_cast<Map*>(entityManager->GetEntity(componentManager->begin<SizeComponent>()->GetOwner()));
    auto content = dynamic_cast<Content*>(entityManager->GetEntity(map->GetContent()));

    PathFinder pathFinder;
    pathFinder.SetHexMapComponent(context.hexMap);
    auto     baseVectorId = content->GetVectorBaseId();
    auto     tankPosition = tank->GetComponent<TransformComponent>()->GetPosition();
    Vector3i nearestBasePos =
        entityManager->GetEntity(baseVectorId[0])->GetComponent<TransformComponent>()->GetPosition();
    pathFinder.Find(tankPosition, nearestBasePos);
    auto minDistance = pathFinder.GetDistance();
    for (int i = 1; i < baseVectorId.size(); i++)
    {
        auto basePosition =
            entityManager->GetEntity(baseVectorId[i])->GetComponent<TransformComponent>()->GetPosition();
        pathFinder.Find(tankPosition, basePosition);
        if (minDistance == PathFinder::NO_PATH ||
            (minDistance > pathFinder.GetDistance() && pathFinder.GetDistance() != PathFinder::NO_PATH))
        {
            nearestBasePos = basePosition;
            minDistance    = pathFinder.GetDistance();
        }
    }
    if (minDistance == PathFinder::NO_PATH)
        return {};
    pathFinder.Find(tankPosition, nearestBasePos);
    auto path = pathFinder.GetShortestPath();
    return path;
}

bool AbstractState::IsPathToBaseExists(GameplaySystem::Context& context, Tank* tank)
{
    auto entityManager    = ecs::ecsEngine->GetEntityManager();
    auto componentManager = ecs::ecsEngine->GetComponentManager();

    auto map     = dynamic_cast<Map*>(entityManager->GetEntity(componentManager->begin<SizeComponent>()->GetOwner()));
    auto content = dynamic_cast<Content*>(entityManager->GetEntity(map->GetContent()));
    auto tankPosition = tank->GetComponent<TransformComponent>()->GetPosition();

    PathFinder pathFinder;
    pathFinder.SetHexMapComponent(context.hexMap);

    auto baseVectorId = content->GetVectorBaseId();
    for (auto& baseId : baseVectorId)
    {
        auto basePosition = entityManager->GetEntity(baseId)->GetComponent<TransformComponent>()->GetPosition();
        pathFinder.Find(tankPosition, basePosition);
        if (pathFinder.GetDistance() != PathFinder::NO_PATH)
            return true;
    }
    return false;
}

bool AbstractState::RepairInMoveArea(GameplaySystem::Context& context,
                                     Tank*                    tank,
                                     Vector3i&                position,
                                     const Repair             type)
{
    auto entityManager    = ecs::ecsEngine->GetEntityManager();
    auto componentManager = ecs::ecsEngine->GetComponentManager();

    auto map     = dynamic_cast<Map*>(entityManager->GetEntity(componentManager->begin<SizeComponent>()->GetOwner()));
    auto content = dynamic_cast<Content*>(entityManager->GetEntity(map->GetContent()));
    auto tankPosition = tank->GetComponent<TransformComponent>()->GetPosition();

    PathFinder pathFinder;
    pathFinder.SetHexMapComponent(context.hexMap);

    auto                  tankSpeed = tank->GetComponent<TtcComponent>()->GetSpeed();
    std::vector<uint64_t> repairVector;
    if (type == Repair::LIGHT)
    {
        repairVector = content->GetVectorLightRepairId();
    }
    else
    {
        repairVector = content->GetVectorHardRepairId();
    }
    for (auto& repairId : repairVector)
    {
        auto repairPosition = entityManager->GetEntity(repairId)->GetComponent<TransformComponent>()->GetPosition();
        pathFinder.Find(tankPosition, repairPosition);
        if (pathFinder.GetDistance() <= tankSpeed && pathFinder.GetDistance() != PathFinder::NO_PATH)
        {
            position = repairPosition;
            return true;
        }
    }
    return false;
}
