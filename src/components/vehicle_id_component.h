#pragma once
#include "ecs.h"

class VehicleIdComponent : public ecs::Component<VehicleIdComponent>
{
public:
    explicit VehicleIdComponent(const int vehicleId)
        : vehicleId(vehicleId)
    {
    }
    ~VehicleIdComponent() override = default;

public:
    void SetVehicleId(const int vehicleId) { this->vehicleId = vehicleId; }
    auto GetVehicleId() const { return this->vehicleId; }

private:
    int vehicleId;
};
