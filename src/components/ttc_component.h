#pragma once

#include "ecs.h"

class TtcComponent : public ecs::Component<TtcComponent>
{
public:
    TtcComponent(const int speed, const int maxHealth, const int damage, const int standartRange)
        : speed(speed)
        , maxHealth(maxHealth)
        , damage(damage)
        , standartRange(standartRange)

    {
    }
    ~TtcComponent() override = default;

public:
    void SetSpeed(const int speed) { this->speed = speed; }
    auto GetSpeed() const { return this->speed; }

    void SetDamage(const int damage) { this->damage = damage; }
    auto GetDamage() const { return this->damage; }

    void SetMaxHealth(const int maxHealth) { this->maxHealth = maxHealth; }
    auto GetMaxHealth() const { return this->maxHealth; }

    void SetStandartRange(const int standartRange) { this->standartRange = standartRange; }
    auto GetStandartRange() const { return this->standartRange; }

private:
    int speed;
    int maxHealth;
    int damage;
    int standartRange;
};
