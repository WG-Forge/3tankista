#pragma once

#include "abstract_state.h"
#include "systems/gameplay_system.h"

class MediumTankInitState;
class MediumTankStaySatte;
class MediumTankMoveState;
class MediumtTankShootState;

class MediumTankInitState : public AbstractState
{
public:
    explicit MediumTankInitState(StateComponent* component)
        : AbstractState(component)
    {
    }
    void UpdateState(GameplaySystem::Context& context) override {}
    void Play(GameplaySystem::Context& context) override {}
};

class MediumTankStayState : public AbstractState
{
};

class MediumTankMoveState : public AbstractState
{
};

class MediumTankShootState : public AbstractState
{
public:
    explicit MediumTankShootState(StateComponent* component)
        : AbstractState(component)
        , target(nullptr)
    {
    }

    void UpdateState(GameplaySystem::Context& context) override
    {
        auto tank = GetCurrentTank();
        // Can attack someone?
        target = nullptr;
        for (auto& enemy : context.enemies)
        {
            if (CanShoot(tank, enemy))
            {
                if (IsCorrectShootPosition(context.hexMap, tank, enemy) &&
                    CheckNeutrality(context.attackMatrix, tank, enemy))
                {
                    if (target == nullptr || target->GetComponent<HealthComponent>()->GetHealth() >
                                                 enemy->GetComponent<HealthComponent>()->GetHealth())
                    {
                        target = enemy;
                    }
                }
            }
        }
    }
    void Play(GameplaySystem::Context& context) override
    {
        auto tank = GetCurrentTank();
        if (target != nullptr)
        {
            ecs::ecsEngine->SendEvent<ShootRequestEvent>(
                ShootModel{ tank->GetComponent<VehicleIdComponent>()->GetVehicleId(), GetShootPosition(tank, target) });
        }
    }

private:
    Tank* target;
};