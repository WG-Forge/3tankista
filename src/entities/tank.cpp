#include "tank.h"
#include "components/shape_component.h"
#include "components/states/at-spg_states.h"
#include "components/states/heavy_states.h"
#include "components/states/light_states.h"
#include "components/states/medium_tank_states.h"
#include "components/states/spg_states.h"
#include "render/materials/default_material.h"
#include "render/materials/material_generator.h"
#include "render/shapes/quad_shape.h"
#include "render/shapes/shape.h"
#include "render/shapes/shape_generator.h"

#include "utility/matrix_transform.h"

Tank::Tank(const ecs::EntityId&      entityId,
           ecs::ComponentManager*    componentManager,
           const Vector3i&           position,
           const AbstractTtcFactory& factory,
           TankType                  type)
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

    const auto transform = GetComponent<TransformComponent>()->GetTransform();

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
            this->stateComponent->ChangeState<HeavyTankInitState>();
            break;
        }
        case TankType::LIGHT:
        {
            this->ttcComponent     = factory.CreateLightTankTtc(this->entityId);
            this->textureComponent = this->AddComponent<TextureComponent>("textures/light.png");
            this->stateComponent->ChangeState<LightTankInitState>();
            break;
        }
        case TankType::SPG:
        {
            this->ttcComponent     = factory.CreateSpgTankTtc(this->entityId);
            this->textureComponent = this->AddComponent<TextureComponent>("textures/spg.png");
            this->stateComponent->ChangeState<SpgTankInitState>();
            break;
        }
        case TankType::AT_SPG:
        {
            this->ttcComponent     = factory.CreateAtSpgTankTtc(this->entityId);
            this->textureComponent = this->AddComponent<TextureComponent>("textures/at_spg.png");
            this->stateComponent->ChangeState<AtSpgTankInitState>();
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

    static const auto aspectRatio = GAME_WINDOW_WIDTH / 1920.0f;

    GetComponent<TransformComponent>()->SetTransform(
        Matrix4f{ { 1.77f * aspectRatio * transform[0], transform[1], transform[2], transform[3] },
                  { transform[4], aspectRatio * transform[5], transform[6], transform[7] },
                  { transform[8], transform[9], transform[10], transform[11] },
                  { transform[12], transform[13], transform[14], transform[15] } });
}
