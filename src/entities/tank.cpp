#include "tank.h"
Tank::Tank()
{
    this->positionComponent =
        AddComponent<PositionComponent>(Vector3i{ 0, 0, 0 });
    this->spawnPositionComponent =
        AddComponent<SpawnPositionComponent>(Vector3i{ 0, 0, 0 });
    this->winPointsComponent = AddComponent<WinPointsComponent>(0, 0);
    this->playerIdComponent  = AddComponent<PlayerIdComponent>(0);
    this->vehicleIdComponent = AddComponent<VehicleIdComponent>(0);
    this->ttcComponent = AddComponent<TTCComponent>(0, 0, 0, TankType::NO_TYPE);
}
