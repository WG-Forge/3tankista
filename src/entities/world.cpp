#include "world.h"

World::World(const ecs::EntityId& entityId, ecs::ComponentManager* componentManager)
    : GameObject<World>(entityId, componentManager)
{
    adapterPlayerIdComponent  = AddComponent<AdapterPlayerIdComponent>();
    adapterVehicleIdComponent = AddComponent<AdapterVehicleIdComponent>();
    hexMapComponent           = AddComponent<HexMapComponent>(0);
    currentPlayerComponent    = AddComponent<CurrentPlayerComponent>(0);
    attackMatrixComponent     = AddComponent<AttackMatrixComponent>();
    turnComponent             = AddComponent<TurnComponent>(0,1);
}
