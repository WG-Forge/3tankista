#pragma once

#include "components/capture_points_component.h"
#include "components/health_component.h"
#include "components/material_component.h"
#include "components/player_id_component.h"
#include "components/spawn_position_component.h"
#include "components/tank_type_component.h"
#include "components/texturecomponent.h"
#include "components/transform_component.h"
#include "components/ttc_component.h"
#include "components/ttc_factories/abstract_factory.h"
#include "components/vehicle_id_component.h"
#include "game/game_object.h"

class Tank : public GameObject<Tank>
{
public:
    Tank(const ecs::EntityId&   entityId,
         ecs::ComponentManager* componentManager,
         const Vector3i&        position,
         const std::string&     textureFileName,
         const AbstractFactory& factory,
         TankType               type);
    ~Tank() override = default;

private:
    PlayerIdComponent*      playerIdComponent;
    VehicleIdComponent*     vehicleIdComponent;
    SpawnPositionComponent* spawnPositionComponent;
    TransformComponent*     transformComponent;
    TtcComponent*           ttcComponent;
    CapturePointsComponent* capturePointsComponent;
    TankTypeComponent*      tankTypeComponent;
    HealthComponent*        healthComponent;
    MaterialComponent*      materialComponent;
    TextureComponent*       textureComponent;
};
