#pragma once

#include "components/adapter_player_id_component.h"
#include "components/adapter_vehicle_id_component.h"
#include "ecs.h"

class World : public ecs::Entity<World>
{
public:
    World();
    ~World() override = default;

private:
    AdapterPlayerIdComponent*  adapterPlayerIdComponent;
    AdapterVehicleIdComponent* adapterVehicleIdComponent;
};
