#ifndef GAMEPLAYACTIONS_H
#define GAMEPLAYACTIONS_H

#include "actiondata.h"
#include "server.h"

#include "nlohmann/json.hpp"

class GamePlayAction
{
public:
    GamePlayAction();

public:
    void       SetPlayerId(const int playerId) { this->playerId = playerId; }
    auto       GetPlayerId() { return this->playerId; }
    const auto GetPlayerId() const { return this->playerId; }

    void           SetType(const Server::Action type) { this->type = type; }
    Server::Action GetType() { return this->type; }
    const Server::Action GetType() const { return this->type; }

    void              SetData(const ActionData& data) { this->data = data; }
    ActionData&       GetData() { return this->data; }
    const ActionData& GetData() const { return this->data; }

private:
    int            playerId;
    Server::Action type;
    ActionData     data;
};

void to_json(nlohmann::json& json, const GamePlayAction& gamePlayAction);

void from_json(const nlohmann::json& json, GamePlayAction& gamePlayAction);

#endif // GAMEACTIONS_H
