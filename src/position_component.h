#pragma once

#include "matrix.hpp"

#include "../third_party/ecs/src/ecs.h"

class PositionComponent : public ecs::Component<PositionComponent>
{
public:
    PositionComponent() = default;
    explicit PositionComponent(const Vector3i& position);

    virtual ~PositionComponent() = default;

public:
    void  SetPosition(const Vector3i& position) { this->position = position; }
    auto& GetPosition() { return this->position; }
    const auto& GetPosition() const { return this->position; }

private:
    Vector3i position;
};
