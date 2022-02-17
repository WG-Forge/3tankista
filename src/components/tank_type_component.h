#pragma once

#include "ecs.h"
#include "utility/matrix.hpp"
#include "utility/tank_types.h"

class TankTypeComponent : public ecs::Component<TankTypeComponent>
{
public:
    TankTypeComponent() = default;
    explicit TankTypeComponent(const TankType tankType)
        : tankType(tankType)
    {
    }
    ~TankTypeComponent() override = default;

public:
    void SetTankType(const TankType tankType) { this->tankType = tankType; }
    auto GetTankType() const { return this->tankType; }

private:
    TankType tankType;
};
