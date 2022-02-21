#pragma once

#include "components/capture_points_component.h"
#include "components/kill_points_component.h"
#include "components/name_component.h"
#include "components/order_component.h"
#include "components/player_id_component.h"
#include "game/game_object.h"

class Player : public GameObject<Player>
{
public:
    Player(const ecs::EntityId& entityId, ecs::ComponentManager* componentManager);
    explicit Player(const ecs::EntityId&   entityId,
                    ecs::ComponentManager* componentManager,
                    uint64_t               playerId,
                    std::string            name);
    ~Player() override = default;

private:
    PlayerIdComponent*      playerIdComponent;
    NameComponent*          nameComponent;
    KillPointsComponent*    killPointsComponent;
    CapturePointsComponent* capturePointsComponent;
    OrderComponent*         orderComponent;
};
