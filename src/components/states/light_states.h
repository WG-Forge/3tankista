#pragma once

#include "abstract_state.h"
#include "systems/gameplay_system.h"
#include "utility/path_finder.h"

class LightTankInitState;
class LightTankStayState;
class LightTankMoveState;
class LightTankShootState;
class LightTankAwayState;

class LightTankInitState : public AbstractState
{
public:
    explicit LightTankInitState(StateComponent* component)
        : AbstractState(component)
    {
    }
    void UpdateState(GameplaySystem::Context& context) override
    {
        auto tank = GetCurrentTank();
        if (GetEnemyInShootArea(context, tank) != nullptr)
        {
            ChangeState<LightTankShootState>();
            return;
        }
        if (!IsOnTheBase(context, tank) && IsPathToBaseExists(context, tank))
        {
            ChangeState<LightTankMoveState>();
            return;
        }
        else
        {
            ChangeState<LightTankStayState>();
            return;
        }
    }
    void Play(GameplaySystem::Context& context) override
    {
        LogDebug("Tank(id = %d) state is %s", GetCurrentTank()->GetEntityID(), typeid(this).name());
    }
};

class LightTankStayState : public AbstractState
{
public:
    explicit LightTankStayState(StateComponent* component)
        : AbstractState(component)
    {
    }
    void UpdateState(GameplaySystem::Context& context) override
    {
        auto tank = GetCurrentTank();
        if (GetEnemyInShootArea(context, tank) != nullptr)
        {
            ChangeState<LightTankShootState>();
            return;
        }
        if (!IsOnTheBase(context, tank) && IsPathToBaseExists(context, tank))
        {
            ChangeState<LightTankMoveState>();
            return;
        }
        Vector3i position{};
        if (IsOnTheBase(context, tank) && FarFreeReachableBasePosition(context, tank, position))
        {
            if ((!IsUnderEnemyShootArea(context, position) &&
                 !(tank->GetComponent<TransformComponent>()->GetPosition() == position)))
            {
                this->ChangeState<LightTankAwayState>();
                return;
            }
        }
    }
    void Play(GameplaySystem::Context& context) override
    {
        LogDebug("Tank(id = %d) state is %s", GetCurrentTank()->GetEntityID(), typeid(this).name());
    }
};

class LightTankMoveState : public AbstractState
{
public:
    explicit LightTankMoveState(StateComponent* component)
        : AbstractState(component)
    {
    }
    void UpdateState(GameplaySystem::Context& context) override
    {
        auto tank = GetCurrentTank();
        if (GetEnemyInShootArea(context, tank) != nullptr)
        {
            ChangeState<LightTankShootState>();
            return;
        }
        Vector3i position{};
        if (IsOnTheBase(context, tank) && FarFreeReachableBasePosition(context, tank, position))
        {
            if (IsUnderEnemyShootArea(context, position) ||
                tank->GetComponent<TransformComponent>()->GetPosition() == position)
            {
                this->ChangeState<LightTankStayState>();
                return;
            }
            else
            {
                this->ChangeState<LightTankAwayState>();
                return;
            }
        }
        if (IsOnTheBase(context, tank) || !IsPathToBaseExists(context, tank))
        {
            ChangeState<LightTankStayState>();
            return;
        }
    }

    void Play(GameplaySystem::Context& context) override
    {
        LogDebug("Tank(id = %d) state is %s", GetCurrentTank()->GetEntityID(), typeid(this).name());
        auto tank = GetCurrentTank();
        auto path = GetPathToBase(context, tank);
        MapUtility::RemoveHexMapComponentCell(
            context.hexMap, tank->GetComponent<TransformComponent>()->GetPosition(), CellState::FRIEND);
        MapUtility::AddHexMapComponentCell(
            context.hexMap,
            path[std::min((int)path.size(), tank->GetComponent<TtcComponent>()->GetSpeed()) - 1],
            CellState::FRIEND);
        ecs::ecsEngine->SendEvent<MoveRequestEvent>(
            MoveModel{ tank->GetComponent<VehicleIdComponent>()->GetVehicleId(),
                       path[std::min((int)path.size(), tank->GetComponent<TtcComponent>()->GetSpeed()) - 1] });
    }
};

class LightTankShootState : public AbstractState
{
public:
    explicit LightTankShootState(StateComponent* component)
        : AbstractState(component)
    {
    }

    void UpdateState(GameplaySystem::Context& context) override
    {
        auto tank = GetCurrentTank();
        if (GetEnemyInShootArea(context, tank) == nullptr)
        {
            if (!IsOnTheBase(context, tank) && IsPathToBaseExists(context, tank))
            {
                ChangeState<LightTankMoveState>();
                return;
            }
            else
            {
                Vector3i position{};
                if (IsOnTheBase(context, tank) && FarFreeReachableBasePosition(context, tank, position))
                {
                    if (IsUnderEnemyShootArea(context, position) ||
                        tank->GetComponent<TransformComponent>()->GetPosition() == position)
                    {
                        this->ChangeState<LightTankStayState>();
                        return;
                    }
                    else
                    {
                        this->ChangeState<LightTankAwayState>();
                        return;
                    }
                }
                ChangeState<LightTankStayState>();
                return;
            }
        }
    }

    void Play(GameplaySystem::Context& context) override
    {

        LogDebug("Tank(id = %d) state is %s", GetCurrentTank()->GetEntityID(), typeid(this).name());
        auto tank = GetCurrentTank();
        auto a =
            ecs::ecsEngine->GetComponentManager()->GetComponent<TransformComponent>(tank->GetEntityID())->GetPosition();
        auto target = GetEnemyInShootArea(context, tank);
        ecs::ecsEngine->SendEvent<ShootRequestEvent>(
            ShootModel{ tank->GetComponent<VehicleIdComponent>()->GetVehicleId(), GetShootPosition(tank, target) });
    }
};

class LightTankAwayState : public AbstractState
{
public:
    explicit LightTankAwayState(StateComponent* component)
        : AbstractState(component)
    {
    }
    void UpdateState(GameplaySystem::Context& context) override
    {
        auto     tank     = GetCurrentTank();
        bool     needHeal = (tank->GetComponent<TtcComponent>()->GetMaxHealth() -
                         tank->GetComponent<HealthComponent>()->GetHealth()) > 0;
        Vector3i position{};
        if (GetEnemyInShootArea(context, tank) != nullptr)
        {
            ChangeState<LightTankShootState>();
            return;
        }
        if (IsOnTheBase(context, tank) && FarFreeReachableBasePosition(context, tank, position))
        {
            if (IsUnderEnemyShootArea(context, position) ||
                tank->GetComponent<TransformComponent>()->GetPosition() == position)
            {
                this->ChangeState<LightTankStayState>();
                return;
            }
        }
    }
    void Play(GameplaySystem::Context& context) override
    {

        LogDebug("Tank(id = %d) state is %s", GetCurrentTank()->GetEntityID(), typeid(this).name());
        auto     tank = GetCurrentTank();
        Vector3i position{};
        FarFreeReachableBasePosition(context, tank, position);
        PathFinder pathFinder;
        pathFinder.SetHexMapComponent(context.hexMap);
        pathFinder.Find(tank->GetComponent<TransformComponent>()->GetPosition(), position);
        auto path = pathFinder.GetShortestPath();
        MapUtility::RemoveHexMapComponentCell(
            context.hexMap, tank->GetComponent<TransformComponent>()->GetPosition(), CellState::FRIEND);
        MapUtility::AddHexMapComponentCell(
            context.hexMap,
            path[std::min((int)path.size(), tank->GetComponent<TtcComponent>()->GetSpeed()) - 1],
            CellState::FRIEND);
        ecs::ecsEngine->SendEvent<MoveRequestEvent>(
            MoveModel{ tank->GetComponent<VehicleIdComponent>()->GetVehicleId(),
                       path[std::min((int)path.size(), tank->GetComponent<TtcComponent>()->GetSpeed()) - 1] });
    }
};
