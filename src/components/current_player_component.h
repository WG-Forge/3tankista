#pragma once

#include "ecs.h"

class CurrentPlayerComponent : public ecs::Component<CurrentPlayerComponent>
{
public:
    explicit CurrentPlayerComponent(int playerId)
        : currentPlayerId(playerId)
    {
    }
    ~CurrentPlayerComponent() override = default;

    auto GetCurrentPlayerId() const { return currentPlayerId; }
    void SetCurrentPlayerId(const int playerId) { currentPlayerId = playerId; }

private:
    int currentPlayerId;
};
