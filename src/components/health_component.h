#pragma once

#include "utility/matrix.hpp"

#include "ecs.h"

class HealthComponent : public ecs::Component<HealthComponent>
{
public:
    HealthComponent() = default;
    HealthComponent(const int health)
        : health(health)
    {
    }
    ~HealthComponent() override = default;

public:
    void SetHealth(const int health) { this->health = health; }
    auto GetHealth() const { return this->health; }

private:
    int health;
};
