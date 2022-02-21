#pragma once
#include "ecs.h"

class VehicleIdComponent : public ecs::Component<VehicleIdComponent>
{
public:
    explicit VehicleIdComponent(const uint64_t& vehicleId)
        : vehicleId(vehicleId)
    {
    }
    ~VehicleIdComponent() override = default;

public:
    void SetVehicleId(const uint64_t vehicleId) { this->vehicleId = vehicleId; }
    auto GetVehicleId() const { return this->vehicleId; }

private:
    uint64_t vehicleId;
};
