#pragma once

#include "utility/matrix.hpp"

#include "ecs.h"

class ShootRangeBonusComponent : public ecs::Component<ShootRangeBonusComponent>
{
public:
    ShootRangeBonusComponent() = default;
    ShootRangeBonusComponent(const int shootRangeBonus)
        : shootRangeBonus(shootRangeBonus)
    {
    }
    ~ShootRangeBonusComponent() override = default;

public:
    void SetShootRangeBonus(const int shootRangeBonus) { this->shootRangeBonus = shootRangeBonus; }
    auto GetShootRangeBonus() const { return this->shootRangeBonus; }

private:
    int shootRangeBonus;
};
