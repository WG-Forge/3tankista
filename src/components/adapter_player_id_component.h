#pragma once

#include "ecs.h"
#include "game/game_events.h"

class AdapterPlayerIdComponent : public ecs::Component<AdapterPlayerIdComponent>
{
public:
    AdapterPlayerIdComponent()
        : adaptationTable()
    {
    }
    ~AdapterPlayerIdComponent() override = default;

    GameObjectId Get(int playerId) const { return adaptationTable.at(playerId); }

    void Add(int playerId, GameObjectId gameObjectId) { adaptationTable[playerId] = gameObjectId; }

    void Remove(int playerId) { adaptationTable.erase(playerId); }

private:
    std::unordered_map<int, GameObjectId> adaptationTable;
};
