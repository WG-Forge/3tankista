#pragma once

#include "abstract_state.h"
#include "systems/gameplay_system.h"
#include "utility/path_finder.h"

class MediumTankInitState;
class MediumTankStayState;
class MediumTankMoveState;
class MediumTankShootState;
class MediumTankHealState;

class MediumTankInitState : public AbstractState
{
public:
    explicit MediumTankInitState(StateComponent* component)
        : AbstractState(component)
    {
    }
    void UpdateState(GameplaySystem::Context& context) override
    {
        auto tank = GetCurrentTank();
        if (GetEnemyInShootArea(context, tank) != nullptr)
        {
            ChangeState<MediumTankShootState>();
            return;
        }
        if (!IsOnTheBase(context, tank) && IsPathToBaseExists(context, tank))
        {
            ChangeState<MediumTankMoveState>();
            return;
        }
        else
        {
            ChangeState<MediumTankStayState>();
            return;
        }
    }
    void Play(GameplaySystem::Context& context) override {}
};

class MediumTankStayState : public AbstractState
{
public:
    explicit MediumTankStayState(StateComponent* component)
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
            ChangeState<MediumTankShootState>();
            return;
        }
        if (needHeal && RepairInMoveArea(context, tank, position, Repair::LIGHT))
        {
            ChangeState<MediumTankHealState>();
            return;
        }
        if (!IsOnTheBase(context, tank) && IsPathToBaseExists(context, tank))
        {
            ChangeState<MediumTankMoveState>();
            return;
        }
    }
    void Play(GameplaySystem::Context& context) override {}
};

class MediumTankMoveState : public AbstractState
{
public:
    explicit MediumTankMoveState(StateComponent* component)
        : AbstractState(component)
    {
    }
    void UpdateState(GameplaySystem::Context& context) override
    {
        auto     tank     = GetCurrentTank();
        bool     needHeal = (tank->GetComponent<TtcComponent>()->GetMaxHealth() -
                         tank->GetComponent<HealthComponent>()->GetHealth()) > 0;
        Vector3i position{};
        if (needHeal && RepairInMoveArea(context, tank, position, Repair::LIGHT))
        {
            ChangeState<MediumTankHealState>();
            return;
        }
        if (GetEnemyInShootArea(context, tank) != nullptr)
        {
            ChangeState<MediumTankShootState>();
            return;
        }
        if (IsOnTheBase(context, tank) || !IsPathToBaseExists(context, tank))
        {
            ChangeState<MediumTankStayState>();
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

class MediumTankShootState : public AbstractState
{
public:
    explicit MediumTankShootState(StateComponent* component)
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
            if (needHeal && RepairInMoveArea(context, tank, position, Repair::LIGHT))
            {
                ChangeState<MediumTankHealState>();
                return;
            }
            if (!IsOnTheBase(context, tank) && IsPathToBaseExists(context, tank))
            {
                ChangeState<MediumTankMoveState>();
                return;
            }
            else
            {
                ChangeState<MediumTankStayState>();
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

class MediumTankHealState : public AbstractState
{
public:
    explicit MediumTankHealState(StateComponent* component)
        : AbstractState(component)
    {
    }
    void UpdateState(GameplaySystem::Context& context) override
    {
        auto tank = GetCurrentTank();
        if (GetEnemyInShootArea(context, tank) != nullptr)
        {
            ChangeState<MediumTankShootState>();
            return;
        }
        if (!IsOnTheBase(context, tank) && IsPathToBaseExists(context, tank))
        {
            ChangeState<MediumTankMoveState>();
            return;
        }
        else
        {
            ChangeState<MediumTankStayState>();
            return;
        }
    }

    void Play(GameplaySystem::Context& context) override
    {
        auto     tank = GetCurrentTank();
        Vector3i position{};
        RepairInMoveArea(context, tank, position, Repair::LIGHT);
        MapUtility::RemoveHexMapComponentCell(
            context.hexMap, tank->GetComponent<TransformComponent>()->GetPosition(), CellState::FRIEND);
        MapUtility::AddHexMapComponentCell(context.hexMap, position, CellState::FRIEND);
        ecs::ecsEngine->SendEvent<MoveRequestEvent>(
            MoveModel{ tank->GetComponent<VehicleIdComponent>()->GetVehicleId(), position });
    }
};