#pragma once

#include "ecs.h"
#include "game/game_events.h"

class AdapterVehicleIdComponent : public ecs::Component<AdapterVehicleIdComponent>
{
public:
    AdapterVehicleIdComponent()
        : adaptationTable()
    {
    }
    ~AdapterVehicleIdComponent() override = default;

    GameObjectId Get(uint64_t vehicleId) const { return adaptationTable.at(vehicleId); }
    uint64_t     GetServerId(GameObjectId id) const { return reverseTable.at(id); }

    void Add(uint64_t vehicleId, GameObjectId gameObjectId)
    {
        adaptationTable[vehicleId] = gameObjectId;
        reverseTable[gameObjectId] = vehicleId;
    }

    void Remove(uint64_t vehicleId)
    {
        reverseTable.erase(adaptationTable[vehicleId]);
        adaptationTable.erase(vehicleId);
    }

private:
    std::unordered_map<uint64_t, GameObjectId> adaptationTable;
    std::map<GameObjectId, uint64_t>           reverseTable;
};
