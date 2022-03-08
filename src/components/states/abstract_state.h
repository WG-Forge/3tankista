#pragma once

#include "components/state_component.h"
#include "ecs.h"
#include "game/models/models.h"
#include "systems/gameplay_system.h"

class AbstractState
{
public:
    explicit AbstractState(StateComponent* component)
        : stateComponent(component)
    {
    }

    virtual void UpdateState(GameplaySystem::Context& context) = 0;
    virtual void Play(GameplaySystem::Context& context)        = 0;

protected:
    template <typename T>
    void ChangeState();

    Tank* GetCurrentTank() { return (Tank*)ecs::ecsEngine->GetEntityManager()->GetEntity(stateComponent->GetOwner()); }

    static bool     CheckNeutrality(AttackMatrixComponent* attackMatrixComponent, Tank* playerTank, Tank* enemyTank);
    static bool     CanShoot(Tank* playerTank, Tank* enemyTank);
    static bool     IsCorrectShootPosition(HexMapComponent* map, Tank* tank, Tank* enemy);
    static Vector3i GetShootPosition(Tank* tank, Tank* enemyTank);
    static Tank*    GetEnemyInShootArea(GameplaySystem::Context& context, Tank* tank);
    static bool     IsOnTheBase(GameplaySystem::Context& context, Tank* tank);
    static bool     IsPathToBaseExists(GameplaySystem::Context& context, Tank* tank);
    static std::vector<Vector3i> GetPathToBase(GameplaySystem::Context& context, Tank* tank);

private:
    StateComponent* stateComponent;
};

template <typename T>
void AbstractState::ChangeState()
{
    this->stateComponent->ChangeState<T>();
}
