#pragma once

#include "components/adapter_player_id_component.h"
#include "components/adapter_vehicle_id_component.h"
#include "components/attack_matrix_component.h"
#include "components/current_player_component.h"
#include "components/hex_map_component.h"
#include "ecs.h"

class World : public ecs::Entity<World>
{
public:
    World();
    ~World() override = default;

private:
    AdapterPlayerIdComponent*  adapterPlayerIdComponent;
    AdapterVehicleIdComponent* adapterVehicleIdComponent;
    HexMapComponent*           hexMapComponent;
    CurrentPlayerComponent*    currentPlayerComponent;
    AttackMatrixComponent*     attackMatrixComponent;
};
