#pragma once

#include "components/health_component.h"
#include "components/player_id_component.h"
#include "components/position_component.h"
#include "components/spawn_position_component.h"
#include "components/ttc_component.h"
#include "components/ttc_factories/abstract_factory.h"
#include "components/vehicle_id_component.h"
#include "components/win_points_component.h"
#include "game/game_object.h"

class Tank : public GameObject<Tank>
{
public:
    Tank();
    Tank(const AbstractFactory& factory, TankType type);
    ~Tank() override = default;

private:
    PlayerIdComponent*      playerIdComponent;
    VehicleIdComponent*     vehicleIdComponent;
    SpawnPositionComponent* spawnPositionComponent;
    PositionComponent*      positionComponent;
    TtcComponent*           ttcComponent;
    WinPointsComponent*     winPointsComponent;
};
