#include "tank.h"

#include "components/shape_component.h"

#include "render_utility/material_generator.h"
#include "render_utility/texture_material.h"

#include "render_utility/quad_shape.h"
#include "render_utility/shape_generator.h"

Tank::Tank(const ecs::EntityId&   entityId,
           ecs::ComponentManager* componentManager,
           const Vector3i&        position,
           const std::string&     textureFileName)
    : GameObject<Tank>(entityId, componentManager)
{
    Shape shape = ShapeGenerator::CreateShape<QuadShape>();

    this->AddComponent<ShapeComponent>(shape);

    this->transformComponent = AddComponent<TransformComponent>(position);
    //    this->spawnPositionComponent =
    //        AddComponent<SpawnPositionComponent>(Vector3i{ 0, 0, 0 });
    //    this->winPointsComponent = AddComponent<WinPointsComponent>(0, 0);
    //    this->playerIdComponent  = AddComponent<PlayerIdComponent>(0);
    //    this->vehicleIdComponent = AddComponent<VehicleIdComponent>(0);
    //    this->ttcComponent = AddComponent<TTCComponent>(0, 0, 0,
    //    TankType::NO_TYPE);
    this->materialComponent = this->AddComponent<MaterialComponent>(
        MaterialGenerator::CreateMaterial<TextureMaterial>(textureFileName),
        Color{ 1.0f, 1.0f, 1.0f, 1.0f });
}
