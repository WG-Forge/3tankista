#include "gameplayaction.h"

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
    gamePlayAction.SetPlayerId(json.at("player_id"));
    json.at("data").get_to(gamePlayAction.GetData());
    gamePlayAction.SetType({ json.at("action_type") });
}
