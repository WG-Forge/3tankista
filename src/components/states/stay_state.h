#pragma once

#include "abstract_state.h"

class StayState : public AbstractState
{
public:
    explicit StayState(uint64_t componentId)
        : AbstractState(componentId)
    {
    }

    void UpdateState() override {}
    void Play() override { std::cerr << "STAY"; } // Just do nothing
};
