#pragma once

#include "ecs.h"
#include "game/game.h"

class MainPlayerComponent : public ecs::Component<MainPlayerComponent>
{
public:
    explicit MainPlayerComponent(uint64_t playerId)
        : mainPlayerId(playerId)
    {
    }
    ~MainPlayerComponent() override = default;

    void SetCurrentPlayerId(const uint64_t playerId) { mainPlayerId = playerId; }
    auto GetCurrentPlayerId() const { return mainPlayerId; }

private:
    uint64_t mainPlayerId;
};
