#pragma once

#include "abstract_state.h"
#include "systems/gameplay_system.h"
#include "utility/path_finder.h"

class AtSpgTankInitState;
class AtSpgTankStayState;
class AtSpgTankMoveState;
class AtSpgTankShootState;
class AtSpgTankHealState;

class AtSpgTankInitState : public AbstractState
{
public:
    explicit AtSpgTankInitState(StateComponent* component)
        : AbstractState(component)
    {
    }
    void UpdateState(GameplaySystem::Context& context) override
    {
        auto tank = GetCurrentTank();
        if (GetEnemyInShootArea(context, tank) != nullptr)
        {
            ChangeState<AtSpgTankShootState>();
            return;
        }
        if (!IsOnTheBase(context, tank) && IsPathToBaseExists(context, tank))
        {
            ChangeState<AtSpgTankMoveState>();
            return;
        }
        else
        {
            ChangeState<AtSpgTankStayState>();
            return;
        }
    }
    void Play(GameplaySystem::Context& context) override {}
};

class AtSpgTankStayState : public AbstractState
{
public:
    explicit AtSpgTankStayState(StateComponent* component)
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
            ChangeState<AtSpgTankShootState>();
            return;
        }
        if (!IsOnTheBase(context, tank) && needHeal && RepairInMoveArea(context, tank, position, Repair::HARD))
        {
            ChangeState<AtSpgTankHealState>();
            return;
        }
        if (!IsOnTheBase(context, tank) && IsPathToBaseExists(context, tank))
        {
            ChangeState<AtSpgTankMoveState>();
            return;
        }
    }
    void Play(GameplaySystem::Context& context) override {}
};

class AtSpgTankMoveState : public AbstractState
{
public:
    explicit AtSpgTankMoveState(StateComponent* component)
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
            ChangeState<AtSpgTankHealState>();
            return;
        }
        if (GetEnemyInShootArea(context, tank) != nullptr)
        {
            ChangeState<AtSpgTankShootState>();
            return;
        }
        if (IsOnTheBase(context, tank) || !IsPathToBaseExists(context, tank))
        {
            ChangeState<AtSpgTankStayState>();
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

class AtSpgTankShootState : public AbstractState
{
public:
    explicit AtSpgTankShootState(StateComponent* component)
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
                ChangeState<AtSpgTankHealState>();
                return;
            }
            if (!IsOnTheBase(context, tank) && IsPathToBaseExists(context, tank))
            {
                ChangeState<AtSpgTankMoveState>();
                return;
            }
            else
            {
                ChangeState<AtSpgTankStayState>();
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

class AtSpgTankHealState : public AbstractState
{
public:
    explicit AtSpgTankHealState(StateComponent* component)
        : AbstractState(component)
    {
    }
    void UpdateState(GameplaySystem::Context& context) override
    {
        auto tank = GetCurrentTank();
        if (GetEnemyInShootArea(context, tank) != nullptr)
        {
            ChangeState<AtSpgTankShootState>();
            return;
        }
        if (!IsOnTheBase(context, tank) && IsPathToBaseExists(context, tank))
        {
            ChangeState<AtSpgTankMoveState>();
            return;
        }
        else
        {
            ChangeState<AtSpgTankStayState>();
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