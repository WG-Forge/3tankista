#pragma once

#include "abstract_state.h"
#include "systems/gameplay_system.h"
#include "utility/path_finder.h"

class SpgTankInitState;
class SpgTankStayState;
class SpgTankMoveState;
class SpgTankShootState;

class SpgTankInitState : public AbstractState
{
public:
    explicit SpgTankInitState(StateComponent* component)
        : AbstractState(component)
    {
    }
    void UpdateState(GameplaySystem::Context& context) override
    {
        auto tank = GetCurrentTank();
        if (GetEnemyInShootArea(context, tank) != nullptr)
        {
            ChangeState<SpgTankShootState>();
            return;
        }
        if (!IsOnTheBase(context, tank) && IsPathToBaseExists(context, tank))
        {
            ChangeState<SpgTankMoveState>();
            return;
        }
        else
        {
            ChangeState<SpgTankStayState>();
            return;
        }
    }
    void Play(GameplaySystem::Context& context) override
    {
        LogDebug("Tank(id = %d) state is %s", GetCurrentTank()->GetEntityID(), typeid(this).name());
    }
};

class SpgTankStayState : public AbstractState
{
public:
    explicit SpgTankStayState(StateComponent* component)
        : AbstractState(component)
    {
    }
    void UpdateState(GameplaySystem::Context& context) override
    {
        auto tank = GetCurrentTank();
        if (GetEnemyInShootArea(context, tank) != nullptr)
        {
            ChangeState<SpgTankShootState>();
            return;
        }
        if (!IsOnTheBase(context, tank) && IsPathToBaseExists(context, tank))
        {
            ChangeState<SpgTankMoveState>();
            return;
        }
    }
    void Play(GameplaySystem::Context& context) override
    {
        LogDebug("Tank(id = %d) state is %s", GetCurrentTank()->GetEntityID(), typeid(this).name());
    }
};

class SpgTankMoveState : public AbstractState
{
public:
    explicit SpgTankMoveState(StateComponent* component)
        : AbstractState(component)
    {
    }
    void UpdateState(GameplaySystem::Context& context) override
    {
        auto tank = GetCurrentTank();
        if (GetEnemyInShootArea(context, tank) != nullptr)
        {
            ChangeState<SpgTankShootState>();
            return;
        }
        if (IsOnTheBase(context, tank) || !IsPathToBaseExists(context, tank))
        {
            ChangeState<SpgTankStayState>();
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

class SpgTankShootState : public AbstractState
{
public:
    explicit SpgTankShootState(StateComponent* component)
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
                ChangeState<SpgTankMoveState>();
                return;
            }
            else
            {
                ChangeState<SpgTankStayState>();
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
