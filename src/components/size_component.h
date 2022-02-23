#pragma once

#include "utility/matrix.hpp"

#include "ecs.h"

class SizeComponent : public ecs::Component<SizeComponent>
{
public:
    SizeComponent() = default;
    SizeComponent(const int size)
        : size(size)
    {
    }
    ~SizeComponent() override = default;

public:
    void SetSize(const int size) { this->size = size; }
    auto GetSize() const { return this->size; }

private:
    int size;
};
