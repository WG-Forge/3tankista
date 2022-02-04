#pragma once

#include <vector>

#include "gameplay_action.h"

class GameActions
{
public:
    GameActions();

public:
    void SetActions(const std::vector<GamePlayAction>& actions)
    {
        this->actions = actions;
    }
    std::vector<GamePlayAction>&       GetActions() { return this->actions; }
    const std::vector<GamePlayAction>& GetActions() const
    {
        return this->actions;
    }

private:
    std::vector<GamePlayAction> actions;
};

void to_json(nlohmann::json& json, const GameActions& gameActions);

void from_json(const nlohmann::json& json, GameActions& gameActions);
