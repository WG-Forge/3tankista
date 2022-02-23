#include "gameplay_system.h"
#include "components/attack_matrix_component.h"
#include "components/base_id_component.h"
#include "components/main_player_component.h"
#include "components/observer_component.h"
#include "components/obstacle_id_component.h"
#include "components/order_component.h"
#include "components/turn_component.h"
#include "entities/tank.h"
#include "win_system.h"
#include <queue>

const std::vector<Vector2i> GameplaySystem::PathFinder::HEX_DIRECTIONS = { { 1, 0 },  { 1, -1 }, { 0, -1 },
                                                                           { -1, 0 }, { -1, 1 }, { 0, 1 } };

GameplaySystem::GameplaySystem()
    : pathFinder()
{
    RegisterEventCallbacks();
}

GameplaySystem::~GameplaySystem()
{
    UnregisterEventCallbacks();
}

Vector2i GameplaySystem::Cube2Hex(const Vector3i& point)
{
    return Vector2i(point.x(), point.z());
}

Vector3i GameplaySystem::Hex2Cube(const Vector2i& point)
{
    return Vector3i(point.x(), -point.x() - point.y(), point.y());
}

int GameplaySystem::GetDistance(const Vector3i& first, const Vector3i& second)
{
    return (abs(first.x() - second.x()) + abs(first.y() - second.y()) + abs(first.z() - second.z())) / 2;
}

int GameplaySystem::GetDistance(const Vector2i& first, const Vector2i& second)
{
    return GetDistance(Hex2Cube(first), Hex2Cube(second));
}

Vector3i GameplaySystem::Shift(const Vector3i& position, int value)
{
    return Vector3i(position.x() + value, position.y() + value, position.z() + value);
}

Vector2i GameplaySystem::Shift(const Vector2i& position, int value)
{
    return Vector2i(position.x() + value, position.y() + value);
}

bool GameplaySystem::IsValid(const Vector2i& point, const int size)
{
    return GetDistance(point, Vector2i(size, size)) <= size;
}

bool GameplaySystem::IsValid(const Vector3i& point, const int size)
{
    return IsValid(Shift(Cube2Hex(point), size), size);
}

void GameplaySystem::SetHexMapComponentCell(HexMapComponent* component,
                                            const Vector3i&  position,
                                            const CellState& state)
{
    component->SetCell(Shift(Cube2Hex(position), component->GetSize()), state);
}

CellState GameplaySystem::GetHexMapComponentCell(HexMapComponent* component, const Vector3i& position)
{
    return component->GetCell(Shift(Cube2Hex(position), component->GetSize()));
}

void GameplaySystem::PathFinder::Bfs(const Vector2i& from)
{
    this->used.assign((area->GetSize() << 1) | 1, std::vector<bool>((area->GetSize() << 1) | 1, false));
    this->lastDirections.assign((area->GetSize() << 1) | 1, std::vector<signed char>((area->GetSize() << 1) | 1, -1));
    this->distance.assign((area->GetSize() << 1) | 1, std::vector<int>((area->GetSize() << 1) | 1, NO_PATH));
    std::queue<Vector2i> q;
    q.push(from);
    this->used[from.x()][from.y()]     = true;
    this->distance[from.x()][from.y()] = 0;
    while (!q.empty())
    {
        auto now = q.front();
        q.pop();
        for (int i = 0; i < HEX_DIRECTIONS.size(); i++)
        {
            auto destination = now + HEX_DIRECTIONS[i];
            if (!GameplaySystem::IsValid(destination, area->GetSize()) ||
                area->GetCell(destination) != CellState::EMPTY)
                continue;
            if (!this->used[destination.x()][destination.y()])
            {
                this->used[destination.x()][destination.y()]           = true;
                this->lastDirections[destination.x()][destination.y()] = i;
                this->distance[destination.x()][destination.y()]       = distance[now.x()][now.y()] + 1;
                q.push(destination);
            }
        }
    }
}

int GameplaySystem::PathFinder::GetDistance(const Vector3i& point)
{
    auto newPoint = GameplaySystem::Shift(GameplaySystem::Cube2Hex(point), area->GetSize());
    return distance[newPoint.x()][newPoint.y()];
}

std::vector<Vector3i> GameplaySystem::PathFinder::GetShortestPath(const Vector3i& point)
{
    Vector2i              now = GameplaySystem::Shift(GameplaySystem::Cube2Hex(point), area->GetSize());
    std::vector<Vector3i> result;
    if (distance[now.x()][now.y()] == NO_PATH)
        return result;
    while (!(now == startPoint))
    {
        result.push_back(GameplaySystem::Hex2Cube(GameplaySystem::Shift(now, -(area->GetSize()))));
        now -= HEX_DIRECTIONS[lastDirections[now.x()][now.y()]];
    }
    std::reverse(result.begin(), result.end());
    return result;
}

void GameplaySystem::OnPlayEvent(const PlayEvent* event)
{
    auto entityManager    = ecs::ecsEngine->GetEntityManager();
    auto componentManager = ecs::ecsEngine->GetComponentManager();
    auto gameArea         = componentManager->begin<HexMapComponent>().operator->();
    auto mainPlayerId     = componentManager->begin<MainPlayerComponent>()->GetMainPlayerId();

    auto turnComponent = componentManager->begin<TurnComponent>().operator->();
    uint64_t                                                      currentPlayerId;
    for (auto it = componentManager->begin<OrderComponent>(); componentManager->end<OrderComponent>() != it; ++it)
    {
        if (it->GetOrder() == turnComponent->GetCurrentTurn() % turnComponent->GetPlayersNumber())
        {
            currentPlayerId = it->GetOwner();
        }
    }

    if (mainPlayerId == currentPlayerId &&
        !entityManager->GetEntity(mainPlayerId)->GetComponent<ObserverComponent>()->GetIsObserver())
    {
        std::vector<Tank*> currentPlayerTanks;
        std::vector<Tank*> enemies;
        for (auto it = componentManager->begin<VehicleIdComponent>(); componentManager->end<VehicleIdComponent>() != it;
             ++it)
        {
            auto tank = (Tank*)entityManager->GetEntity(it->GetVehicleId());
            if (tank->GetComponent<PlayerIdComponent>()->GetPlayerId() == mainPlayerId)
            {
                currentPlayerTanks.push_back(tank);
            }
            else
            {
                enemies.push_back(tank);
            }
        }
        std::sort(currentPlayerTanks.begin(),
                  currentPlayerTanks.end(),
                  [](Tank* lhs, Tank* rhs)
                  {
                      return lhs->GetComponent<TankTypeComponent>()->GetTankType() <
                             rhs->GetComponent<TankTypeComponent>()->GetTankType();
                  });
        for (auto tank : currentPlayerTanks)
        {
            // Can attack someone?
            Tank* target = nullptr;
            for (auto& enemy : enemies)
            {
                if (CanShoot(tank, enemy))
                {
                    if (IsCorrectShootPosition(tank, enemy) && CheckNeutrality(tank, enemy))
                    {
                        if (target == nullptr || target->GetComponent<HealthComponent>()->GetHealth() >
                                                     enemy->GetComponent<HealthComponent>()->GetHealth())
                        {
                            target = enemy;
                        }
                    }
                }
            }

            if (target != nullptr)
            {
                ecs::ecsEngine->SendEvent<ShootRequestEvent>(ShootModel{
                    tank->GetComponent<VehicleIdComponent>()->GetVehicleId(), GetShootPosition(tank, target) });
            }
            else
            {
                // Move to the nearest base
                pathFinder.SetHexMapComponent(gameArea);
                pathFinder.SetStartPoint(tank->GetComponent<TransformComponent>()->GetPosition());
                auto     it = componentManager->begin<BaseIdComponent>();
                Vector3i nearestBasePos =
                    entityManager->GetEntity(it->GetOwner())->GetComponent<TransformComponent>()->GetPosition();
                ++it;
                for (; componentManager->end<BaseIdComponent>() != it; ++it)
                {
                    auto basePosition =
                        entityManager->GetEntity(it->GetOwner())->GetComponent<TransformComponent>()->GetPosition();
                    if (pathFinder.GetDistance(nearestBasePos) == PathFinder::NO_PATH ||
                        (pathFinder.GetDistance(nearestBasePos) > pathFinder.GetDistance(basePosition) &&
                         pathFinder.GetDistance(basePosition) != PathFinder::NO_PATH))
                    {
                        nearestBasePos = basePosition;
                    }
                }
                if (pathFinder.GetDistance(nearestBasePos) == PathFinder::NO_PATH)
                    continue; // STAY
                auto path = pathFinder.GetShortestPath(nearestBasePos);
                if (path.empty())
                    continue; // STAY
                SetHexMapComponentCell(
                    gameArea, tank->GetComponent<TransformComponent>()->GetPosition(), CellState::EMPTY);
                SetHexMapComponentCell(
                    gameArea,
                    path[std::min((int)path.size(), tank->GetComponent<TtcComponent>()->GetSpeed()) - 1],
                    CellState::FRIEND);
                ecs::ecsEngine->SendEvent<MoveRequestEvent>(
                    MoveModel{ tank->GetComponent<VehicleIdComponent>()->GetVehicleId(),
                               path[std::min((int)path.size(), tank->GetComponent<TtcComponent>()->GetSpeed()) - 1] });
            }
        }
    }
    auto attackMatrix = componentManager->begin<AttackMatrixComponent>().operator->();
    attackMatrix->ClearUserAttacks(currentPlayerId);
    ecs::ecsEngine->SendEvent<TurnRequestEvent>();
    ecs::ecsEngine->SendEvent<GameActionsRequestEvent>();
}

bool GameplaySystem::CheckNeutrality(Tank* playerTank, Tank* enemyTank)
{
    auto attackMatrixComponent = ecs::ecsEngine->GetComponentManager()->begin<AttackMatrixComponent>();
    auto tankPlayerId          = playerTank->GetComponent<PlayerIdComponent>()->GetPlayerId();
    auto enemyPlayerId         = enemyTank->GetComponent<PlayerIdComponent>()->GetPlayerId();
    std::cout << "gameplay: "
              << ", tank: " << tankPlayerId << ", enemy: " << enemyPlayerId << "\n";
    for (auto& [key, value] : attackMatrixComponent->GetAttackMatrix())
    {
        std::cout << key << " {";
        for (auto& id : value)
        {
            std::cout << id << ", ";
        }
        std::cout << "}\n";
    }
    // If he attacked us
    if (attackMatrixComponent->IsAttacked(enemyPlayerId, tankPlayerId))
        return true;
    std::cout << "after\n";
    // If he attacked by somebody else
    auto attackMatrix = attackMatrixComponent->GetAttackMatrix();
    for (auto& [who, whom] : attackMatrix)
    {
        if (who == tankPlayerId)
            continue;
        std::cout << "aaafter: " << who << "\n";
        if (whom.find(enemyPlayerId) != whom.end())
            return false;
    }
    return true;
}

bool GameplaySystem::CanShoot(Tank* playerTank, Tank* enemyTank)
{
    bool shoot    = false;
    auto distance = GameplaySystem::GetDistance(playerTank->GetComponent<TransformComponent>()->GetPosition(),
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
            shoot = GameplaySystem::GetDistance(enemyTank->GetComponent<TransformComponent>()->GetPosition(),
                                                playerTank->GetComponent<TransformComponent>()->GetPosition()) ==
                    MEDIUM_TANK_DAMAGE_DISTANCE;
            break;
        }
        default:
            break;
    }

    return shoot;
}

Vector3i GameplaySystem::GetShootPosition(Tank* tank, Tank* enemyTank)
{

    auto enemyPosition = enemyTank->GetComponent<TransformComponent>()->GetPosition();
    auto tankPosition  = tank->GetComponent<TransformComponent>()->GetPosition();
    switch (tank->GetComponent<TankTypeComponent>()->GetTankType())
    {

        case TankType::AT_SPG:
        {
            int      distance = GameplaySystem::GetDistance(enemyPosition, tankPosition);
            Vector3i delta    = enemyPosition - tankPosition;
            enemyPosition     = tankPosition + delta / distance;

            break;
        }
        default:

            break;
    }

    return enemyPosition;
}

bool GameplaySystem::IsCorrectShootPosition(Tank* tank, Tank* enemy)
{

    bool result   = false;
    auto position = enemy->GetComponent<TransformComponent>()->GetPosition();
    if (tank->GetComponent<TankTypeComponent>()->GetTankType() == TankType::AT_SPG)
    {
        if (pathFinder.GetDistance(position) != -1 &&
            pathFinder.GetDistance(position) ==
                GameplaySystem::GetDistance(tank->GetComponent<TransformComponent>()->GetPosition(), position))
        {
            result = true;
        }
    }
    else
    {
        result = GameplaySystem::GetHexMapComponentCell(
                     ecs::ecsEngine->GetComponentManager()->begin<HexMapComponent>().operator->(), position) !=
                 CellState::OBSTACLE;
    }
    return result;
}

void GameplaySystem::RegisterEventCallbacks()
{
    RegisterEventCallback(&GameplaySystem::OnPlayEvent);
}

void GameplaySystem::UnregisterEventCallbacks()
{
    UnregisterEventCallback(&GameplaySystem::OnPlayEvent);
}
