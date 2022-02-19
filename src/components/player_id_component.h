#pragma once
#include "ecs.h"

class PlayerIdComponent : public ecs::Component<PlayerIdComponent>
{
public:
    explicit PlayerIdComponent(const uint64_t playerId)
        : playerId(playerId)
    {
    }
    ~PlayerIdComponent() override = default;

public:
    void SetPlayerId(const uint64_t playerId) { this->playerId = playerId; }
    auto GetPlayerId() const { return this->playerId; }

private:
    uint64_t playerId;
};