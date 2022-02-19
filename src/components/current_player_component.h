#pragma once

#include "ecs.h"
#include "game/game.h"
class CurrentPlayerComponent : public ecs::Component<CurrentPlayerComponent>
{
public:
    explicit CurrentPlayerComponent(uint64_t playerId)
        : currentPlayerId(playerId)
    {
    }
    ~CurrentPlayerComponent() override = default;

    void SetCurrentPlayerId(const uint64_t playerId) { currentPlayerId = playerId; }
    auto GetCurrentPlayerId() const { return currentPlayerId; }

private:
    uint64_t currentPlayerId;
};
