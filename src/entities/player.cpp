#include "player.h"

Player::Player()
{
    this->playerIdComponent = AddComponent<PlayerIdComponent>(0);
}

Player::Player(const int playerId)
{
    this->playerIdComponent = AddComponent<PlayerIdComponent>(playerId);
}
