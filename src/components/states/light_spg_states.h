#pragma once

#include "abstract_state.h"
#include "components/base_id_component.h"
#include "systems/gameplay_system.h"
#include "utility/path_finder.h"

class LightSpgTankInitState;
class LightSpgTankStayState;
class LightSpgTankMoveState;
class LightSpgTankShootState;

/**
 * Initial state. Should be assigned when tank destroyed or spawned.
 * Transitions:
 *      Move => anyway we should go to the base
 */
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
        }
        if (!IsOnTheBase(context, tank) && IsPathToBaseExists(context, tank))
            ChangeState<LightSpgTankMoveState>();
        else
            ChangeState<LightSpgTankStayState>();
    }
    void Play(GameplaySystem::Context& context) override {}
};

/**
 * Tank is on the base and earn capturePoints
 * Transitions:
 *      Shoot => if there is an enemy
 *      Move => if we are not on the base
 */
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
        }
        if (!IsOnTheBase(context, tank) && IsPathToBaseExists(context, tank))
            ChangeState<LightSpgTankMoveState>();
    }
    void Play(GameplaySystem::Context& context) override {}
};

/**
 * Tank is not on the base and there is no enemy
 * Transitions:
 *      Shoot => if there is an enemy
 *      Stay => if tank is on the base or there is no path
 */
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
        }
        if (IsOnTheBase(context, tank) || !IsPathToBaseExists(context, tank))
            ChangeState<LightSpgTankStayState>();
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

/**
 * There is an enemy in Area(attack)
 * Transitions:
 *      Move -> no enemy
 *      Stay -> is on the base
 */
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
                ChangeState<LightSpgTankMoveState>();
            else
                ChangeState<LightSpgTankStayState>();
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
