#include "tank.h"
Tank::Tank(const ecs::EntityId&   entityId,
           ecs::ComponentManager* componentManager)
    : GameObject<Tank>(entityId, componentManager)
{
    this->positionComponent =
        AddComponent<PositionComponent>(Vector3i{ 0, 0, 0 });
    this->spawnPositionComponent =
        AddComponent<SpawnPositionComponent>(Vector3i{ 0, 0, 0 });
    this->capturePointsComponent = AddComponent<CapturePointsComponent>(0);
    this->playerIdComponent      = AddComponent<PlayerIdComponent>(0);
    this->vehicleIdComponent     = AddComponent<VehicleIdComponent>(0);
    this->ttcComponent           = AddComponent<TTCComponent>(0, 0, 0);
    this->tankTypeComponent =
        AddComponent<TankTypeComponent>(TankType::NO_TYPE);
}
