#pragma once

#include "action_data.h"
#include "nlohmann/json.hpp"
#include "server/server.h"

class GamePlayAction
{
public:
    GamePlayAction() = default;

public:
    void       SetPlayerId(const int playerId) { this->playerId = playerId; }
    auto       GetPlayerId() { return this->playerId; }
    const auto GetPlayerId() const { return this->playerId; }

    void           SetType(const Server::Action type) { this->type = type; }
    Server::Action GetType() { return this->type; }
    const Server::Action GetType() const { return this->type; }

    void        SetData(ActionData& data) { this->data = std::move(data); }
    auto&       GetData() { return this->data; }
    const auto& GetData() const { return this->data; }

private:
    int            playerId;
    Server::Action type;
    ActionData     data;
};

void to_json(nlohmann::json& json, const GamePlayAction& gamePlayAction);

void from_json(const nlohmann::json& json, GamePlayAction& gamePlayAction);
