#pragma once
#include "ecs.h"

class KillPointsComponent : public ecs::Component<KillPointsComponent>
{
public:
    KillPointsComponent(const int killPoints)
        : killPoints(killPoints)
    {
    }
    ~KillPointsComponent() override = default;

public:
    void SetKillPoints(const int killPoints) { this->killPoints = killPoints; }
    auto GetKillPoints() const { return this->killPoints; }

private:
    int killPoints;
};
