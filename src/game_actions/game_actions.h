#pragma once

#include "gameplay_action.h"
#include <vector>

class GameActions
{
public:
    GameActions();

public:
    void SetActions(std::vector<GamePlayAction>& actions)
    {
        this->actions = std::move(actions);
    }
    auto&       GetActions() { return this->actions; }
    const auto& GetActions() const { return this->actions; }

private:
    std::vector<GamePlayAction> actions;
};

void to_json(nlohmann::json& json, const GameActions& gameActions);

void from_json(const nlohmann::json& json, GameActions& gameActions);
