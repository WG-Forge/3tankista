#include "player.h"

Player::Player()
    : data()
    , vehicles()
{
}

Player::~Player() {}
void to_json(nlohmann::json& j, const Player& pl) {}

void from_json(const nlohmann::json& j, Player& p)
{
    ServerModels::from_json(j, p.GetData());
}