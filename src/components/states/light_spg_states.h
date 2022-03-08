#pragma once

#include "abstract_state.h"
#include "systems/gameplay_system.h"
#include "utility/path_finder.h"

class LightSpgTankInitState;
class LightSpgTankStayState;
class LightSpgTankMoveState;
class LightSpgTankShootState;

class LightSpgTankInitState : public AbstractState
{
public:
    explicit LightSpgTankInitState(StateComponent* component)
        : AbstractState(component)
    {
    }
    void UpdateState(GameplaySystem::Context& context) override
    {
        auto tank = GetCurrentTank();
        if (GetEnemyInShootArea(context, tank) != nullptr)
        {
            ChangeState<LightSpgTankShootState>();
            return;
        }
        if (!IsOnTheBase(context, tank) && IsPathToBaseExists(context, tank))
        {
            ChangeState<LightSpgTankMoveState>();
            return;
        }
        else
        {
            ChangeState<LightSpgTankStayState>();
            return;
        }
    }
    void Play(GameplaySystem::Context& context) override {}
};

class LightSpgTankStayState : public AbstractState
{
public:
    explicit LightSpgTankStayState(StateComponent* component)
        : AbstractState(component)
    {
    }
    void UpdateState(GameplaySystem::Context& context) override
    {
        auto tank = GetCurrentTank();
        if (GetEnemyInShootArea(context, tank) != nullptr)
        {
            ChangeState<LightSpgTankShootState>();
            return;
        }
        if (!IsOnTheBase(context, tank) && IsPathToBaseExists(context, tank))
        {
            ChangeState<LightSpgTankMoveState>();
            return;
        }
    }
    void Play(GameplaySystem::Context& context) override {}
};

class LightSpgTankMoveState : public AbstractState
{
public:
    explicit LightSpgTankMoveState(StateComponent* component)
        : AbstractState(component)
    {
    }
    void UpdateState(GameplaySystem::Context& context) override
    {
        auto tank = GetCurrentTank();
        if (GetEnemyInShootArea(context, tank) != nullptr)
        {
            ChangeState<LightSpgTankShootState>();
            return;
        }
        if (IsOnTheBase(context, tank) || !IsPathToBaseExists(context, tank))
        {
            ChangeState<LightSpgTankStayState>();
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

class LightSpgTankShootState : public AbstractState
{
public:
    explicit LightSpgTankShootState(StateComponent* component)
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
                ChangeState<LightSpgTankMoveState>();
                return;
            }
            else
            {
                ChangeState<LightSpgTankStayState>();
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
