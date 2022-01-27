#include "player.h"

Player::Player()
    : data()
    , vehicles()
{
}

Player::~Player() {}

void to_json(nlohmann::json& json, const Player& player)
{
    json = nlohmann::json{ "" };
}

void from_json(const nlohmann::json& json, Player& player)
{
    json.get_to(player.GetData());
}
