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

    uint64_t Get(uint64_t playerId) const { return adaptationTable.at(playerId); }
    uint64_t GetServerId(uint64_t id) const { return reverseTable.at(id); }

    void Add(uint64_t playerId, GameObjectId gameObjectId)
    {
        adaptationTable[playerId]  = gameObjectId;
        reverseTable[gameObjectId] = playerId;
    }

    void Remove(uint64_t playerId)
    {
        reverseTable.erase(adaptationTable[playerId]);
        adaptationTable.erase(playerId);
    }

private:
    std::unordered_map<uint64_t, uint64_t> adaptationTable;
    std::unordered_map<uint64_t, uint64_t> reverseTable;
};
