#pragma once

#include "utility/matrix.hpp"

#include "ecs.h"

class UsageComponent : public ecs::Component<UsageComponent>
{
public:
    UsageComponent() = default;
    UsageComponent(const int usage)
        : usage(usage)
    {
    }
    ~UsageComponent() override = default;

public:
    void SetUsage(const int usage) { this->usage = usage; }
    auto GetUsage() const { return this->usage; }

private:
    int usage;
};
