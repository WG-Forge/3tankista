#pragma once

#include "abstract_state.h"
#include "systems/gameplay_system.h"
#include "utility/path_finder.h"

class HeavyAtSpgTankInitState;
class HeavyAtSpgTankStayState;
class HeavyAtSpgTankMoveState;
class HeavyAtSpgTankShootState;
class HeavyAtSpgTankHealState;

class HeavyAtSpgTankInitState : public AbstractState
{
public:
    explicit HeavyAtSpgTankInitState(StateComponent* component)
        : AbstractState(component)
    {
    }
    void UpdateState(GameplaySystem::Context& context) override
    {
        auto tank = GetCurrentTank();
        if (GetEnemyInShootArea(context, tank) != nullptr)
        {
            ChangeState<HeavyAtSpgTankShootState>();
            return;
        }
        if (!IsOnTheBase(context, tank) && IsPathToBaseExists(context, tank))
        {
            ChangeState<HeavyAtSpgTankMoveState>();
            return;
        }
        else
        {
            ChangeState<HeavyAtSpgTankStayState>();
            return;
        }
    }
    void Play(GameplaySystem::Context& context) override {}
};

class HeavyAtSpgTankStayState : public AbstractState
{
public:
    explicit HeavyAtSpgTankStayState(StateComponent* component)
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
            ChangeState<HeavyAtSpgTankShootState>();
            return;
        }
        if (needHeal && HardRepairInMoveArea(context, tank, position))
        {
            ChangeState<HeavyAtSpgTankHealState>();
            return;
        }
        if (!IsOnTheBase(context, tank) && IsPathToBaseExists(context, tank))
        {
            ChangeState<HeavyAtSpgTankMoveState>();
            return;
        }
    }
    void Play(GameplaySystem::Context& context) override {}
};

class HeavyAtSpgTankMoveState : public AbstractState
{
public:
    explicit HeavyAtSpgTankMoveState(StateComponent* component)
        : AbstractState(component)
    {
    }
    void UpdateState(GameplaySystem::Context& context) override
    {
        auto     tank     = GetCurrentTank();
        bool     needHeal = (tank->GetComponent<TtcComponent>()->GetMaxHealth() -
                         tank->GetComponent<HealthComponent>()->GetHealth()) > 0;
        Vector3i position{};
        if (needHeal && HardRepairInMoveArea(context, tank, position))
        {
            ChangeState<HeavyAtSpgTankHealState>();
            return;
        }
        if (GetEnemyInShootArea(context, tank) != nullptr)
        {
            ChangeState<HeavyAtSpgTankShootState>();
            return;
        }
        if (IsOnTheBase(context, tank) || !IsPathToBaseExists(context, tank))
        {
            ChangeState<HeavyAtSpgTankStayState>();
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

class HeavyAtSpgTankShootState : public AbstractState
{
public:
    explicit HeavyAtSpgTankShootState(StateComponent* component)
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
            if (needHeal && HardRepairInMoveArea(context, tank, position))
            {
                ChangeState<HeavyAtSpgTankHealState>();
                return;
            }
            if (!IsOnTheBase(context, tank) && IsPathToBaseExists(context, tank))
            {
                ChangeState<HeavyAtSpgTankMoveState>();
                return;
            }
            else
            {
                ChangeState<HeavyAtSpgTankStayState>();
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

class HeavyAtSpgTankHealState : public AbstractState
{
public:
    explicit HeavyAtSpgTankHealState(StateComponent* component)
        : AbstractState(component)
    {
    }
    void UpdateState(GameplaySystem::Context& context) override
    {
        auto tank = GetCurrentTank();
        if (GetEnemyInShootArea(context, tank) != nullptr)
        {
            ChangeState<HeavyAtSpgTankShootState>();
            return;
        }
        if (!IsOnTheBase(context, tank) && IsPathToBaseExists(context, tank))
        {
            ChangeState<HeavyAtSpgTankMoveState>();
            return;
        }
        else
        {
            ChangeState<HeavyAtSpgTankStayState>();
            return;
        }
    }

    void Play(GameplaySystem::Context& context) override
    {
        auto     tank = GetCurrentTank();
        Vector3i position{};
        HardRepairInMoveArea(context, tank, position);

        MapUtility::RemoveHexMapComponentCell(
            context.hexMap, tank->GetComponent<TransformComponent>()->GetPosition(), CellState::FRIEND);
        MapUtility::AddHexMapComponentCell(context.hexMap, position, CellState::FRIEND);
        ecs::ecsEngine->SendEvent<MoveRequestEvent>(
            MoveModel{ tank->GetComponent<VehicleIdComponent>()->GetVehicleId(), position });
    }
};