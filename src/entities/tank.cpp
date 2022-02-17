#include "tank.h"
Tank::Tank(const ecs::EntityId& entityId, ecs::ComponentManager* componentManager)
    : GameObject<Tank>(entityId, componentManager)
{
    this->positionComponent      = AddComponent<PositionComponent>(Vector3i{ 0, 0, 0 });
    this->spawnPositionComponent = AddComponent<SpawnPositionComponent>(Vector3i{ 0, 0, 0 });
    this->capturePointsComponent = AddComponent<CapturePointsComponent>(0);
    this->playerIdComponent      = AddComponent<PlayerIdComponent>(0);
    this->vehicleIdComponent     = AddComponent<VehicleIdComponent>(0);
    this->ttcComponent           = AddComponent<TtcComponent>(0, 0, 0);
    this->tankTypeComponent      = AddComponent<TankTypeComponent>(TankType::NO_TYPE);
}

Tank::Tank(const ecs::EntityId&   entityId,
           ecs::ComponentManager* componentManager,
           const AbstractFactory& factory,
           TankType               type)
    : GameObject<Tank>(entityId, componentManager)
{
    this->positionComponent      = AddComponent<PositionComponent>(Vector3i{ 0, 0, 0 });
    this->spawnPositionComponent = AddComponent<SpawnPositionComponent>(Vector3i{ 0, 0, 0 });
    this->capturePointsComponent = AddComponent<CapturePointsComponent>(0);
    this->playerIdComponent      = AddComponent<PlayerIdComponent>(0);
    this->vehicleIdComponent     = AddComponent<VehicleIdComponent>(0);
    this->tankTypeComponent      = AddComponent<TankTypeComponent>(type);
    switch (type)
    {
        case TankType::MEDIUM:
        {
            this->ttcComponent = factory.CreateMediumTankTtc(this->entityId);

            break;
        }
        case TankType::HEAVY:
        {
            this->ttcComponent = factory.CreateHeavyTankTtc(this->entityId);
            break;
        }
        case TankType::LIGHT:
        {
            this->ttcComponent = factory.CreateLightTankTtc(this->entityId);
            break;
        }
        case TankType::SPG:
        {
            this->ttcComponent = factory.CreateSpgTankTtc(this->entityId);
            break;
        }
        case TankType::AT_SPG:
        {
            this->ttcComponent = factory.CreateAtSpgTankTtc(this->entityId);
            break;
        }
    }
}
