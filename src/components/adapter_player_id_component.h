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
    int          GetServerId(GameObjectId id) const { return reverseTable.at(id); }

    void Add(int playerId, GameObjectId gameObjectId)
    {
        adaptationTable[playerId]  = gameObjectId;
        reverseTable[gameObjectId] = playerId;
    }

    void Remove(int playerId)
    {
        reverseTable.erase(adaptationTable[playerId]);
        adaptationTable.erase(playerId);
    }

private:
    std::unordered_map<int, GameObjectId> adaptationTable;
    std::map<GameObjectId, int>           reverseTable;
};
