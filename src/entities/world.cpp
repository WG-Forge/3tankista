#include "world.h"

World::World()
{
    adapterPlayerIdComponent  = AddComponent<AdapterPlayerIdComponent>();
    adapterVehicleIdComponent = AddComponent<AdapterVehicleIdComponent>();
    hexMapComponent = AddComponent<HexMapComponent>(0);
}
