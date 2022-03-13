#pragma once

#include "abstract_state.h"
#include "systems/gameplay_system.h"
#include "utility/path_finder.h"

class LightTankInitState;
class LightTankStayState;
class LightTankMoveState;
class LightTankShootState;

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
    void Play(GameplaySystem::Context& context) override {}
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
    }
    void Play(GameplaySystem::Context& context) override {}
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
        if (IsOnTheBase(context, tank) || !IsPathToBaseExists(context, tank))
        {
            ChangeState<LightTankStayState>();
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
                ChangeState<LightTankStayState>();
                return;
            }
        }
    }

    void Play(GameplaySystem::Context& context) override
    {
        auto tank = GetCurrentTank();
        auto a =
            ecs::ecsEngine->GetComponentManager()->GetComponent<TransformComponent>(tank->GetEntityID())->GetPosition();
        auto target = GetEnemyInShootArea(context, tank);
        ecs::ecsEngine->SendEvent<ShootRequestEvent>(
            ShootModel{ tank->GetComponent<VehicleIdComponent>()->GetVehicleId(), GetShootPosition(tank, target) });
    }
};
