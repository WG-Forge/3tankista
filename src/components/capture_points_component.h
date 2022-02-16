#pragma once
#include "ecs.h"

class CapturePointsComponent : public ecs::Component<CapturePointsComponent>
{
public:
    CapturePointsComponent(const int capturePoints)
        : capturePoints(capturePoints)
    {
    }
    ~CapturePointsComponent() override = default;

public:
    void SetCapturePoints(const int capturePoints)
    {
        this->capturePoints = capturePoints;
    }
    auto GetCapturePoints() const { return this->capturePoints; }

private:
    int capturePoints;
};
