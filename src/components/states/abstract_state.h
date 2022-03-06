#pragma once

#include "ecs.h"

class AbstractState
{
public:
    explicit AbstractState(uint64_t componentId) : componentId(componentId) {}

    virtual void UpdateState() = 0;
    virtual void Play() = 0;

private:
    uint64_t componentId;
};
