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
    this->ttcComponent = AddComponent<TtcComponent>(0, 0, 0, TankType::NO_TYPE);
}

Tank::Tank(const AbstractFactory& factory, TankType type)
{
    this->positionComponent =
        AddComponent<PositionComponent>(Vector3i{ 0, 0, 0 });
    this->spawnPositionComponent =
        AddComponent<SpawnPositionComponent>(Vector3i{ 0, 0, 0 });
    this->winPointsComponent = AddComponent<WinPointsComponent>(0, 0);
    this->playerIdComponent  = AddComponent<PlayerIdComponent>(0);
    this->vehicleIdComponent = AddComponent<VehicleIdComponent>(0);
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
