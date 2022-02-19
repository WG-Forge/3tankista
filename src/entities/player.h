#pragma once

#include "components/capture_points_component.h"
#include "components/kill_points_component.h"
#include "components/player_id_component.h"
#include "game/game_object.h"

class Player : public GameObject<Player>
{
public:
    Player(const ecs::EntityId& entityId, ecs::ComponentManager* componentManager);
    explicit Player(const ecs::EntityId& entityId, ecs::ComponentManager* componentManager, const uint64_t playerId);
    ~Player() override = default;

private:
    PlayerIdComponent*      playerIdComponent;
    KillPointsComponent*    killPointsComponent;
    CapturePointsComponent* capturePointsComponent;
};
