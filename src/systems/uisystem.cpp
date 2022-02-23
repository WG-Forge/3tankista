#include "uisystem.h"

#include "entities/health_bar.h"

#include "components/main_player_component.h"
#include "components/order_component.h"
#include "components/turn_component.h"

UiSystem::UiSystem()
{
    this->RegisterEventCallbacks();
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
                                     return healthBar->vehicleId == event->vehicleId;
                                 });
    if (it != this->healthBarsId.end())
    {
        // изменять tansform matrix черновго квадрата в зависимости соотношения currHp/MaxHp
        // currHp/MaxHp = 1      -> 0
        // currHp/MaxHp = 999999 -> 100

        // варианты: currHp == maxHp -> 0
        //           currHp == 0     -> 100
        //           (other)         x = currHp/maxHp && size = x * sizeHealthBar;

        HealthBar*  healthBar  = (HealthBar*)ecs::ecsEngine->GetEntityManager()->GetEntity(*it);
        std::string healthText = std::to_string(event->health) + " / " + std::to_string(event->maxHealth);
        //        std::cerr << " New hp " << healthText << std::endl << std::flush;
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

        auto componentManager = ecs::ecsEngine->GetComponentManager();
        auto mainPlayerId     = componentManager->begin<MainPlayerComponent>()->GetMainPlayerId();

        const auto newTankHealthBar = ecs::ecsEngine->GetEntityManager()->CreateEntity<HealthBar>(
            tank->GetComponent<VehicleIdComponent>()->GetVehicleId(),
            healthBarTransform,
            tank->GetComponent<PlayerIdComponent>()->GetPlayerId() == mainPlayerId ? FRIEND_HP_TEXTURE_NAME
                                                                                   : ENEMY_HP_TEXTURE_NAME,
            healthString,
            tankTextureName,
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
