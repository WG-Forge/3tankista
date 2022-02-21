#pragma once

#include "ecs.h"
#include "game/game_events.h"

class AttackMatrixComponent : public ecs::Component<AttackMatrixComponent>
{
public:
    AttackMatrixComponent()           = default;
    ~AttackMatrixComponent() override = default;

    void AddAttack(uint64_t who, uint64_t whom)
    {
        if (attackMatrix.find(who) == attackMatrix.end())
            attackMatrix[who] = std::set<uint64_t>();
        attackMatrix[who].insert(whom);
    }

    bool IsAttacked(uint64_t who, uint64_t whom)
    {
        if (attackMatrix.find(who) == attackMatrix.end())
            return false;
        return attackMatrix[who].find(whom) != attackMatrix[who].end();
    }

    const auto& GetAttackMatrix() const { return attackMatrix; }

    void SetAttackMatrix(std::map<uint64_t, std::set<uint64_t>> matrix) { attackMatrix = std::move(matrix); };

    void ClearAttackMatrix() { attackMatrix.clear(); }



private:
    std::map<uint64_t, std::set<uint64_t>> attackMatrix;
};
