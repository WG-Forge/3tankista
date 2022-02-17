#pragma once

#include "components/player_id_component.h"
#include "game/game_object.h"

class Player : public GameObject<Player>
{
public:
    Player(const ecs::EntityId& entityId, ecs::ComponentManager* componentManager);
    explicit Player(const ecs::EntityId& entityId, ecs::ComponentManager* componentManager, int playerId);
    ~Player() override = default;

private:
    PlayerIdComponent* playerIdComponent;
};
