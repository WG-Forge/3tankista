#pragma once

#include "components/health_component.h"
#include "components/material_component.h"
#include "components/player_id_component.h"
#include "components/spawn_position_component.h"
#include "components/texturecomponent.h"
#include "components/transform_component.h"
#include "components/ttc_component.h"
#include "components/vehicle_id_component.h"
#include "components/win_points_component.h"

#include "game/game_object.h"

class Tank : public GameObject<Tank>
{
public:
    Tank(const ecs::EntityId&   entityId,
         ecs::ComponentManager* componentManager,
         const Vector3i&        position,
         const std::string&     textureFileName);
    ~Tank() override = default;

private:
    //    PlayerIdComponent*      playerIdComponent;
    //    VehicleIdComponent*     vehicleIdComponent;
    //    SpawnPositionComponent* spawnPositionComponent;
    TransformComponent* transformComponent;
    //    TTCComponent*           ttcComponent;
    //    WinPointsComponent*     winPointsComponent;
    MaterialComponent* materialComponent;
    TextureComponent*  textureComponent;
};
