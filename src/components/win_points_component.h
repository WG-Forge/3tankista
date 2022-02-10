#pragma once
#include "ecs.h"

class WinPointsComponent : public ecs::Component<WinPointsComponent>
{
public:
    WinPointsComponent(const int capturePoints, const int killPoints)
        : capturePoints(capturePoints)
        , killPoints(killPoints)
    {
    }
    ~WinPointsComponent() override = default;

public:
    void SetCapturePoints(const int capturePoints)
    {
        this->capturePoints = capturePoints;
    }
    auto GetCapturePoints() const { return this->capturePoints; }

    void SetKillPoints(const int killPoints) { this->killPoints = killPoints; }
    auto GetKillPoints() const { return this->killPoints; }

private:
    int capturePoints;
    int killPoints;
};
