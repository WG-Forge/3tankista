#pragma once

#include "abstract_state.h"
#include "systems/gameplay_system.h"
#include "utility/path_finder.h"

class HeavyTankInitState;
class HeavyTankStayState;
class HeavyTankMoveState;
class HeavyTankShootState;
class HeavyTankHealState;

class HeavyTankInitState : public AbstractState
{
public:
    explicit HeavyTankInitState(StateComponent* component)
        : AbstractState(component)
    {
    }
    void UpdateState(GameplaySystem::Context& context) override
    {
        auto tank = GetCurrentTank();
        if (GetEnemyInShootArea(context, tank) != nullptr)
        {
            ChangeState<HeavyTankShootState>();
            return;
        }
        if (!IsOnTheBase(context, tank) && IsPathToBaseExists(context, tank))
        {
            ChangeState<HeavyTankMoveState>();
            return;
        }
        else
        {
            ChangeState<HeavyTankStayState>();
            return;
        }
    }
    void Play(GameplaySystem::Context& context) override {}
};

class HeavyTankStayState : public AbstractState
{
public:
    explicit HeavyTankStayState(StateComponent* component)
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
            ChangeState<HeavyTankShootState>();
            return;
        }
        if (!IsOnTheBase(context, tank) && needHeal && RepairInMoveArea(context, tank, position, Repair::HARD))
        {
            ChangeState<HeavyTankHealState>();
            return;
        }
        if (!IsOnTheBase(context, tank) && IsPathToBaseExists(context, tank))
        {
            ChangeState<HeavyTankMoveState>();
            return;
        }
    }
    void Play(GameplaySystem::Context& context) override {}
};

class HeavyTankMoveState : public AbstractState
{
public:
    explicit HeavyTankMoveState(StateComponent* component)
        : AbstractState(component)
    {
    }
    void UpdateState(GameplaySystem::Context& context) override
    {
        auto     tank     = GetCurrentTank();
        bool     needHeal = (tank->GetComponent<TtcComponent>()->GetMaxHealth() -
                         tank->GetComponent<HealthComponent>()->GetHealth()) > 0;
        Vector3i position{};
        if (needHeal && RepairInMoveArea(context, tank, position, Repair::HARD))
        {
            ChangeState<HeavyTankHealState>();
            return;
        }
        if (GetEnemyInShootArea(context, tank) != nullptr)
        {
            ChangeState<HeavyTankShootState>();
            return;
        }
        if (IsOnTheBase(context, tank) || !IsPathToBaseExists(context, tank))
        {
            ChangeState<HeavyTankStayState>();
            return;
        }
    }

    void Play(GameplaySystem::Context& context) override
    {
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

class HeavyTankShootState : public AbstractState
{
public:
    explicit HeavyTankShootState(StateComponent* component)
        : AbstractState(component)
    {
    }

    void UpdateState(GameplaySystem::Context& context) override
    {
        auto tank = GetCurrentTank();
        if (GetEnemyInShootArea(context, tank) == nullptr)
        {
            bool     needHeal = (tank->GetComponent<TtcComponent>()->GetMaxHealth() -
                             tank->GetComponent<HealthComponent>()->GetHealth()) > 0;
            Vector3i position{};
            if (needHeal && RepairInMoveArea(context, tank, position, Repair::HARD))
            {
                ChangeState<HeavyTankHealState>();
                return;
            }
            if (!IsOnTheBase(context, tank) && IsPathToBaseExists(context, tank))
            {
                ChangeState<HeavyTankMoveState>();
                return;
            }
            else
            {
                ChangeState<HeavyTankStayState>();
                return;
            }
        }
    }

    void Play(GameplaySystem::Context& context) override
    {
        auto tank   = GetCurrentTank();
        auto target = GetEnemyInShootArea(context, tank);
        ecs::ecsEngine->SendEvent<ShootRequestEvent>(
            ShootModel{ tank->GetComponent<VehicleIdComponent>()->GetVehicleId(), GetShootPosition(tank, target) });
    }
};

class HeavyTankHealState : public AbstractState
{
public:
    explicit HeavyTankHealState(StateComponent* component)
        : AbstractState(component)
    {
    }
    void UpdateState(GameplaySystem::Context& context) override
    {
        auto tank = GetCurrentTank();
        if (GetEnemyInShootArea(context, tank) != nullptr)
        {
            ChangeState<HeavyTankShootState>();
            return;
        }
        if (!IsOnTheBase(context, tank) && IsPathToBaseExists(context, tank))
        {
            ChangeState<HeavyTankMoveState>();
            return;
        }
        else
        {
            ChangeState<HeavyTankStayState>();
            return;
        }
    }

    void Play(GameplaySystem::Context& context) override
    {
        auto     tank = GetCurrentTank();
        Vector3i position{};
        RepairInMoveArea(context, tank, position, Repair::HARD);

        MapUtility::RemoveHexMapComponentCell(
            context.hexMap, tank->GetComponent<TransformComponent>()->GetPosition(), CellState::FRIEND);
        MapUtility::AddHexMapComponentCell(context.hexMap, position, CellState::FRIEND);
        ecs::ecsEngine->SendEvent<MoveRequestEvent>(
            MoveModel{ tank->GetComponent<VehicleIdComponent>()->GetVehicleId(), position });
    }
};