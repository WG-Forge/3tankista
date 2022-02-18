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

    GameObjectId Get(int vehicleId) const { return adaptationTable.at(vehicleId); }
    int          GetServerId(GameObjectId id) const { return reverseTable.at(id); }

    void Add(int vehicleId, GameObjectId gameObjectId)
    {
        adaptationTable[vehicleId] = gameObjectId;
        reverseTable[gameObjectId] = vehicleId;
    }

    void Remove(int vehicleId)
    {
        reverseTable.erase(adaptationTable[vehicleId]);
        adaptationTable.erase(vehicleId);
    }

private:
    std::unordered_map<int, GameObjectId> adaptationTable;
    std::map<GameObjectId, int>           reverseTable;
};
