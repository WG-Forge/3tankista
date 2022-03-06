#pragma once

#include "abstract_state.h"
#include "components/base_id_component.h"
#include "systems/gameplay_system.h"
#include "utility/path_finder.h"

class MediumTankInitState;
class MediumTankStayState;
class MediumTankMoveState;
class MediumTankShootState;

/**
 * Initial state. Should be assigned when tank destroyed or spawned.
 * Transitions:
 *      Move => anyway we should go to the base
 */
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
        }
        if (!IsOnTheBase(context, tank) && !GetPathToBase(context, tank).empty())
            ChangeState<MediumTankMoveState>();
        else
            ChangeState<MediumTankStayState>();
    }
    void Play(GameplaySystem::Context& context) override
    {
        std::cerr << "INIT: " << GetCurrentTank()->GetEntityID() << "\n";
    }
};

/**
 * Tank is on the base and earn capturePoints
 * Transitions:
 *      Shoot => if there is an enemy
 *      Move => if we are not on the base
 */
class MediumTankStayState : public AbstractState
{
public:
    explicit MediumTankStayState(StateComponent* component)
        : AbstractState(component)
    {
    }
    void UpdateState(GameplaySystem::Context& context) override
    {
        auto tank = GetCurrentTank();
        if (GetEnemyInShootArea(context, tank) != nullptr)
        {
            ChangeState<MediumTankShootState>();
        }
        if (!IsOnTheBase(context, tank) && !GetPathToBase(context, tank).empty())
            ChangeState<MediumTankMoveState>();
    }
    void Play(GameplaySystem::Context& context) override
    {
        std::cerr << "STAY: " << GetCurrentTank()->GetEntityID() << "\n";
    }
};

/**
 * Tank is not on the base and there is no enemy
 * Transitions:
 *      Shoot => if there is an enemy
 *      Stay => if tank is on the base or there is no path
 */
class MediumTankMoveState : public AbstractState
{
public:
    explicit MediumTankMoveState(StateComponent* component)
        : AbstractState(component)
    {
    }
    void UpdateState(GameplaySystem::Context& context) override
    {
        auto tank = GetCurrentTank();
        if (GetEnemyInShootArea(context, tank) != nullptr)
        {
            ChangeState<MediumTankShootState>();
        }
        if (IsOnTheBase(context, tank) || GetPathToBase(context, tank).empty())
            ChangeState<MediumTankStayState>();
    }

    void Play(GameplaySystem::Context& context) override
    {
        std::cerr << "MOVE: " << GetCurrentTank()->GetEntityID() << "\n";
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
            if (!IsOnTheBase(context, tank) && !GetPathToBase(context, tank).empty())
                ChangeState<MediumTankMoveState>();
            else
                ChangeState<MediumTankStayState>();
        }
    }

    void Play(GameplaySystem::Context& context) override
    {
        std::cerr << "SHOOT: " << GetCurrentTank()->GetEntityID() << "\n";
        auto tank   = GetCurrentTank();
        auto target = GetEnemyInShootArea(context, tank);
        ecs::ecsEngine->SendEvent<ShootRequestEvent>(
            ShootModel{ tank->GetComponent<VehicleIdComponent>()->GetVehicleId(), GetShootPosition(tank, target) });
    }
};