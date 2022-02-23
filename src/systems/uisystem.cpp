#include "uisystem.h"

#include "entities/health_bar.h"

#include "components/main_player_component.h"

UiSystem::UiSystem()
{
    this->RegisterEventCallbacks();

    // create tanks when player joined
    // for create we need: is our tank, color, max hp, transform component
    // transform component we can calc from position vector in pixels (Vector3f)
    // transform matrix and color we can use like uniform and calc it from

    // create health bars
    // save their id
    //    const auto roseAtSpgTankHealthBar =
    //        ecs::ecsEngine->GetEntityManager()->CreateEntity<HealthBar>(Matrix4f{ { 1.0f, 0.0f, 0.0f, 0.7f },
    //                                                                              { 0.0f, 1.0f, 0.0f, 0.2f },
    //                                                                              { 0.0f, 0.0f, 1.0f, 0.0f },
    //                                                                              { 0.0f, 0.0f, 0.0f, 1.0f } },
    //                                                                    FRIEND_HP_TEXTURE_NAME,
    //                                                                    "1 / 1",
    //                                                                    AT_SPG_TANK_TEXTURE_NAME,
    //                                                                    ROSE_SPAWN_COLOR);
    //    healthBarsId.push_back(roseAtSpgTankHealthBar);
    //    const auto roseLightTankHealthBar =
    //        ecs::ecsEngine->GetEntityManager()->CreateEntity<HealthBar>(Matrix4f{ { 1.0f, 0.0f, 0.0f, 0.7f },
    //                                                                              { 0.0f, 1.0f, 0.0f, 0.1f },
    //                                                                              { 0.0f, 0.0f, 1.0f, 0.0f },
    //                                                                              { 0.0f, 0.0f, 0.0f, 1.0f } },
    //                                                                    FRIEND_HP_TEXTURE_NAME,
    //                                                                    "1 / 1",
    //                                                                    LIGHT_TANK_TEXTURE_NAME,
    //                                                                    ROSE_SPAWN_COLOR);
    //    healthBarsId.push_back(roseLightTankHealthBar);
    //    const auto roseHeavyTankHealthBar =
    //        ecs::ecsEngine->GetEntityManager()->CreateEntity<HealthBar>(Matrix4f{ { 1.0f, 0.0f, 0.0f, 0.7f },
    //                                                                              { 0.0f, 1.0f, 0.0f, 0.0f },
    //                                                                              { 0.0f, 0.0f, 1.0f, 0.0f },
    //                                                                              { 0.0f, 0.0f, 0.0f, 1.0f } },
    //                                                                    FRIEND_HP_TEXTURE_NAME,
    //                                                                    "3 / 3",
    //                                                                    HEAVY_TANK_TEXTURE_NAME,
    //                                                                    ROSE_SPAWN_COLOR);
    //    healthBarsId.push_back(roseHeavyTankHealthBar);
    //    const auto roseMediumTankHealthBar =
    //        ecs::ecsEngine->GetEntityManager()->CreateEntity<HealthBar>(Matrix4f{ { 1.0f, 0.0f, 0.0f, 0.7f },
    //                                                                              { 0.0f, 1.0f, 0.0f, -0.1f },
    //                                                                              { 0.0f, 0.0f, 1.0f, 0.0f },
    //                                                                              { 0.0f, 0.0f, 0.0f, 1.0f } },
    //                                                                    FRIEND_HP_TEXTURE_NAME,
    //                                                                    "2 / 2",
    //                                                                    MEDIUM_TANK_TEXTURE_NAME,
    //                                                                    ROSE_SPAWN_COLOR);
    //    healthBarsId.push_back(roseMediumTankHealthBar);
    //    const auto roseSpgTankHealthBar =
    //        ecs::ecsEngine->GetEntityManager()->CreateEntity<HealthBar>(Matrix4f{ { 1.0f, 0.0f, 0.0f, 0.7f },
    //                                                                              { 0.0f, 1.0f, 0.0f, -0.2f },
    //                                                                              { 0.0f, 0.0f, 1.0f, 0.0f },
    //                                                                              { 0.0f, 0.0f, 0.0f, 1.0f } },
    //                                                                    FRIEND_HP_TEXTURE_NAME,
    //                                                                    "2 / 2",
    //                                                                    SPG_TANK_TEXTURE_NAME,
    //                                                                    ROSE_SPAWN_COLOR);
    //    healthBarsId.push_back(roseSpgTankHealthBar);
}

UiSystem::~UiSystem()
{
    this->UnregisterEventCallbacks();
}

void UiSystem::OnHealthChanged(const HealthChanged* event)
{
    // find health bar in saved id and invoke SetHealth()
    const auto it = std::find_if(this->healthBarsId.begin(),
                                 this->healthBarsId.end(),
                                 [&](const GameObjectId& healthBarId)
                                 {
                                     HealthBar* healthBar =
                                         (HealthBar*)ecs::ecsEngine->GetEntityManager()->GetEntity(healthBarId);
                                     return healthBar->vehicleId;
                                 });
    if (it != this->healthBarsId.end())
    {
        HealthBar*  healthBar  = (HealthBar*)ecs::ecsEngine->GetEntityManager()->GetEntity(*it);
        std::string healthText = std::to_string(event->health) + " / " + std::to_string(event->maxHealth);
        healthBar->SetHealth(healthText);
    }
}

void UiSystem::OnNewTankCreated(const NewTankCreated* event)
{
    Tank* tank = (Tank*)ecs::ecsEngine->GetEntityManager()->GetEntity(event->tankId);

    const auto it = std::find_if(
        this->POSSIBLE_HEALTH_BAR_POSITIONS.cbegin(),
        this->POSSIBLE_HEALTH_BAR_POSITIONS.cend(),
        [&](const auto& tuple)
        { return std::get<Vector3i>(tuple) == tank->GetComponent<SpawnPositionComponent>()->GetSpawnPosition(); });

    if (it != this->POSSIBLE_HEALTH_BAR_POSITIONS.cend())
    {
        const auto& healthBarPositionPixel = std::get<Vector3f>(*it);
        Transform   healthBarTransform;
        healthBarTransform.SetPosition(healthBarPositionPixel);

        const auto maxHealth    = tank->GetComponent<TtcComponent>()->GetMaxHealth();
        const auto healthString = std::to_string(maxHealth) + " / " + std::to_string(maxHealth);

        const std::string tankTextureName = this->ChooseTextureForTankHealthBar(tank, std::get<HealthBarPosition>(*it));

        const auto newTankHealthBar = ecs::ecsEngine->GetEntityManager()->CreateEntity<HealthBar>(
            tank->GetComponent<VehicleIdComponent>()->GetVehicleId(),
            healthBarTransform,
            FRIEND_HP_TEXTURE_NAME,
            healthString,
            tankTextureName,
            //            tank->GetComponent<TextureComponent>()->GetTextureFileName(),
            std::get<Color>(*it));
        healthBarsId.push_back(newTankHealthBar);
    }
}

void UiSystem::RegisterEventCallbacks()
{
    this->RegisterEventCallback(&UiSystem::OnHealthChanged);
    this->RegisterEventCallback(&UiSystem::OnNewTankCreated);
}

void UiSystem::UnregisterEventCallbacks()
{
    this->UnregisterEventCallback(&UiSystem::OnHealthChanged);
    this->UnregisterEventCallback(&UiSystem::OnNewTankCreated);
}

std::string UiSystem::ChooseTextureForTankHealthBar(Tank* tank, HealthBarPosition pos) const
{
    std::string healthBarTextureName{ "textures/" };

    switch (pos)
    {
        case HealthBarPosition::TOP_LEFT:
        {
            healthBarTextureName += this->ChooseTextureForTankType(tank);
            healthBarTextureName += "_health_bar_blue.png";
            break;
        }
        case HealthBarPosition::TOP_RIGHT:
        {
            healthBarTextureName += this->ChooseTextureForTankType(tank);
            healthBarTextureName += "_health_bar_blue.png";
            break;
        }
        case HealthBarPosition::MIDDLE_LEFT:
        {
            healthBarTextureName += this->ChooseTextureForTankType(tank);
            healthBarTextureName += "_health_bar_rose.png";
            break;
        }
        case HealthBarPosition::MIDDLE_RIGHT:
        {
            healthBarTextureName += this->ChooseTextureForTankType(tank);
            healthBarTextureName += "_health_bar_rose.png";
            break;
        }
        case HealthBarPosition::BOTTOM_LEFT:
        {
            healthBarTextureName += this->ChooseTextureForTankType(tank);
            healthBarTextureName += "_health_bar_orange.png";
            break;
        }
        case HealthBarPosition::BOTTOM_RIGHT:
        {
            healthBarTextureName += this->ChooseTextureForTankType(tank);
            healthBarTextureName += "_health_bar_orange.png";
            break;
        }
        default:
        {
            break;
        }
    }
    return healthBarTextureName;
}

std::string UiSystem::ChooseTextureForTankType(Tank* tank) const
{
    std::string tankTypeTextureName;

    switch (tank->GetComponent<TankTypeComponent>()->GetTankType())
    {
        case TankType::AT_SPG:
        {
            tankTypeTextureName = "at_spg";
            break;
        }
        case TankType::MEDIUM:
        {
            tankTypeTextureName = "medium";
            break;
        }
        case TankType::HEAVY:
        {
            tankTypeTextureName = "heavy";
            break;
        }
        case TankType::LIGHT:
        {
            tankTypeTextureName = "light";
            break;
        }
        case TankType::SPG:
        {
            tankTypeTextureName = "spg";
            break;
        }
        default:
        {
            break;
        }
    }
    return tankTypeTextureName;
}
