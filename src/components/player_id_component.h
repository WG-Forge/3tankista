#pragma once
#include "ecs.h"

class PlayerIdComponent : public ecs::Component<PlayerIdComponent>
{
public:
    explicit PlayerIdComponent(const int playerId)
        : playerId(playerId)
    {
    }
    ~PlayerIdComponent() override = default;

public:
    void SetPlayerId(const int playerId) { this->playerId = playerId; }
    auto GetPlayerId() const { return this->playerId; }

private:
    int playerId;
};