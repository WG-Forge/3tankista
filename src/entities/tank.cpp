#include "tank.h"
#include "components/shape_component.h"
#include "components/states/heavy_at-spg_states.h"
#include "components/states/light_spg_states.h"
#include "components/states/medium_tank_states.h"
#include "render/materials/default_material.h"
#include "render/materials/material_generator.h"
#include "render/shapes/quad_shape.h"
#include "render/shapes/shape.h"
#include "render/shapes/shape_generator.h"

Tank::Tank(const ecs::EntityId&   entityId,
           ecs::ComponentManager* componentManager,
           const Vector3i&        position,
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
    this->shootRangeBonus        = AddComponent<ShootRangeBonusComponent>(0);
    this->stateComponent         = AddComponent<StateComponent>();
    switch (type)
    {
        case TankType::MEDIUM:
        {
            this->ttcComponent     = factory.CreateMediumTankTtc(this->entityId);
            this->textureComponent = this->AddComponent<TextureComponent>("textures/medium.png");
            this->stateComponent->ChangeState<MediumTankInitState>();
            break;
        }
        case TankType::HEAVY:
        {
            this->ttcComponent     = factory.CreateHeavyTankTtc(this->entityId);
            this->textureComponent = this->AddComponent<TextureComponent>("textures/heavy.png");
            this->stateComponent->ChangeState<HeavyAtSpgTankInitState>();
            break;
        }
        case TankType::LIGHT:
        {
            this->ttcComponent     = factory.CreateLightTankTtc(this->entityId);
            this->textureComponent = this->AddComponent<TextureComponent>("textures/light.png");
            this->stateComponent->ChangeState<LightSpgTankInitState>();
            break;
        }
        case TankType::SPG:
        {
            this->ttcComponent     = factory.CreateSpgTankTtc(this->entityId);
            this->textureComponent = this->AddComponent<TextureComponent>("textures/spg.png");
            this->stateComponent->ChangeState<LightSpgTankInitState>();
            break;
        }
        case TankType::AT_SPG:
        {
            this->ttcComponent     = factory.CreateAtSpgTankTtc(this->entityId);
            this->textureComponent = this->AddComponent<TextureComponent>("textures/at_spg.png");
            this->stateComponent->ChangeState<HeavyAtSpgTankInitState>();
            break;
        }
        case TankType::NO_TYPE:
        {
            break;
        }
        default:
        {
        }
    }
    this->healthComponent   = AddComponent<HealthComponent>(this->ttcComponent->GetMaxHealth());
    this->materialComponent = this->AddComponent<MaterialComponent>(
        MaterialGenerator::CreateMaterial<DefaultMaterial>(), Color{ 1.0f, 1.0f, 1.0f, 1.0f });
}
