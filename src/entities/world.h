#pragma once

#include "components/adapter_player_id_component.h"
#include "components/adapter_vehicle_id_component.h"
#include "components/attack_matrix_component.h"
#include "components/main_player_component.h"
#include "components/hex_map_component.h"
#include "components/turn_component.h"
#include "ecs.h"
#include "game/game_object.h"

class World : public GameObject<World>
{
public:
    World(const ecs::EntityId& entityId, ecs::ComponentManager* componentManager);
    ~World() override = default;

private:
    AdapterPlayerIdComponent*  adapterPlayerIdComponent;
    AdapterVehicleIdComponent* adapterVehicleIdComponent;
    HexMapComponent*           hexMapComponent;
    MainPlayerComponent*       mainPlayerComponent;
    AttackMatrixComponent*     attackMatrixComponent;
    TurnComponent*             turnComponent;
};
