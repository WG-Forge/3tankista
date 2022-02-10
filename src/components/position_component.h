#pragma once

#include "utility/matrix.hpp"

#include "ecs.h"

class PositionComponent : public ecs::Component<PositionComponent>
{
public:
    PositionComponent() = default;
    explicit PositionComponent(const Vector3i& position);
    ~PositionComponent() override = default;

public:
    void  SetPosition(const Vector3i& position) { this->position = position; }
    auto& GetPosition() { return this->position; }
    const auto& GetPosition() const { return this->position; }

private:
    Vector3i position;
};
