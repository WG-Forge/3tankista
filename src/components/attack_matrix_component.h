#pragma once

#include "ecs.h"
#include "game/game_events.h"

class AttackMatrixComponent : public ecs::Component<AttackMatrixComponent>
{
public:
    AttackMatrixComponent()           = default;
    ~AttackMatrixComponent() override = default;

    void AddAttack(GameObjectId who, GameObjectId whom)
    {
        if (attackMatrix.find(who) == attackMatrix.end())
            attackMatrix[who] = std::set<GameObjectId>();
        attackMatrix[who].insert(whom);
    }

    bool IsAttacked(GameObjectId who, GameObjectId whom)
    {
        if (attackMatrix.find(who) == attackMatrix.end())
            return false;
        return attackMatrix[who].find(whom) != attackMatrix[who].end();
    }

    const auto& GetAttackMatrix() const { return attackMatrix; }

    void ClearAttackMatrix() { attackMatrix.clear(); }

private:
    std::map<GameObjectId, std::set<GameObjectId>> attackMatrix;
};
