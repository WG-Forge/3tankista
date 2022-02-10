#pragma once
#include "ecs.h"
#include "utility/matrix.hpp"
#include "utility/tank_types.h"

class TTCComponent : public ecs::Component<TTCComponent>
{
public:
    TTCComponent() = default;
    TTCComponent(const int      speed,
                 const int      maxHealth,
                 const int      damage,
                 const TankType tankType)
        : speed(speed)
        , maxHealth(maxHealth)
        , damage(damage)
        , tankType(tankType)
    {
    }
    ~TTCComponent() override = default;

public:
    void SetSpeed(const int speed) { this->speed = speed; }
    auto GetSpeed() const { return this->speed; }

    void SetDamage(const int damage) { this->damage = damage; }
    auto GetDamage() const { return this->damage; }

    void SetMaxHealth(const int maxHealth) { this->maxHealth = maxHealth; }
    auto GetMaxHealth() const { return this->maxHealth; }

    void SetTankType(const TankType tankType) { this->tankType = tankType; }
    auto GetTankType() const { return this->tankType; }

private:
    int      speed;
    int      maxHealth;
    TankType tankType;
    int      damage;
};
