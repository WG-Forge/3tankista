#pragma once

#include "game/game_object.h"
#include "components/player_id_component.h"

class Player : public GameObject<Player>
{
public:
    Player();
    explicit Player(int playerId);
    ~Player() override = default;

private:
    PlayerIdComponent* playerIdComponent;
};
