#pragma once

#include "components/state_component.h"
#include "ecs.h"
#include "entities/player.h"
#include "enums/repair.h"
#include "game/models/models.h"
#include "systems/gameplay_system.h"

class AbstractState
{
public:
    DECLARE_LOGGER
    explicit AbstractState(StateComponent* component)
        : stateComponent(component)
    {
        DEFINE_LOGGER("TankStateMachine")
    }

    virtual void UpdateState(GameplaySystem::Context& context) = 0;
    virtual void Play(GameplaySystem::Context& context)        = 0;

protected:
    template <typename T>
    void ChangeState();

    Tank* GetCurrentTank() { return (Tank*)ecs::ecsEngine->GetEntityManager()->GetEntity(stateComponent->GetOwner()); }

    static bool     CheckNeutrality(AttackMatrixComponent* attackMatrixComponent, Tank* playerTank, Tank* enemyTank);
    static bool     CanShoot(Tank* tank, const Vector3i& position);
    static bool     IsCorrectShootPosition(HexMapComponent* map, Tank* tank, Tank* enemy);
    static Vector3i GetShootPosition(Tank* tank, Tank* enemyTank);
    static Tank*    GetEnemyInShootArea(GameplaySystem::Context& context, Tank* tank);
    static bool     IsUnderEnemyShootArea(GameplaySystem::Context& context, const Vector3i position);
    static bool     IsOnTheBase(GameplaySystem::Context& context, Tank* tank);
    static bool     IsPathToBaseExists(GameplaySystem::Context& context, Tank* tank);
    static std::vector<Vector3i> GetPathToBase(GameplaySystem::Context& context, Tank* tank);
    static bool RepairInMoveArea(GameplaySystem::Context& context, Tank* tank, Vector3i& position, const Repair type);
    static bool FarFreeReachableBasePosition(GameplaySystem::Context& context, Tank* tank, Vector3i& position);

private:
    StateComponent* stateComponent;
};

template <typename T>
void AbstractState::ChangeState()
{
    this->stateComponent->ChangeState<T>();
}
