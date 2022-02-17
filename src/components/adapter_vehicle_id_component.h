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

    void Add(int vehicleId, GameObjectId gameObjectId) { adaptationTable[vehicleId] = gameObjectId; }

    void Remove(int vehicleId) { adaptationTable.erase(vehicleId); }

private:
    std::unordered_map<int, GameObjectId> adaptationTable;
};
