#include "gameplay_action.h"

GamePlayAction::GamePlayAction()
    : playerId()
    , type()
    , data()
{
}

void to_json(nlohmann::json& json, const GamePlayAction& gamePlayAction)
{
    json = nlohmann::json{ "" };
}

void from_json(const nlohmann::json& json, GamePlayAction& gamePlayAction)
{
    json.at("player_id").get_to(gamePlayAction.GetPlayerId());
    json.at("data").get_to(gamePlayAction.GetData());
    gamePlayAction.SetType({ json.at("action_type") });
}
