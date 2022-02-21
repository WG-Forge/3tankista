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

    void SetMainPlayerId(const uint64_t playerId) { mainPlayerId = playerId; }
    auto GetMainPlayerId() const { return mainPlayerId; }

private:
    uint64_t mainPlayerId;
};
