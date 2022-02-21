#include "tank.h"
#include "components/shape_component.h"
#include "render/materials/default_material.h"
#include "render/materials/material_generator.h"
#include "render/shapes/quad_shape.h"
#include "render/shapes/shape.h"
#include "render/shapes/shape_generator.h"

Tank::Tank(const ecs::EntityId&   entityId,
           ecs::ComponentManager* componentManager,
           const Vector3i&        position,
           const std::string&     textureFileName,
           const AbstractFactory& factory,
           TankType               type)
    : GameObject<Tank>(entityId, componentManager)
{
    Shape shape = ShapeGenerator::CreateShape<QuadShape>();
    this->AddComponent<ShapeComponent>(shape);
    this->transformComponent     = AddComponent<TransformComponent>(position);
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
    this->healthComponent   = AddComponent<HealthComponent>(this->ttcComponent->GetMaxHealth());
    this->textureComponent  = this->AddComponent<TextureComponent>(textureFileName);
    this->materialComponent = this->AddComponent<MaterialComponent>(
        MaterialGenerator::CreateMaterial<DefaultMaterial>(), Color{ 1.0f, 1.0f, 1.0f, 1.0f });
}
