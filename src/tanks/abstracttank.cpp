#include "abstracttank.h"
AbstractTank::AbstractTank(int vehicleId, const TankType& tankType)
    : vehicleId(vehicleId)
    , tankType(tankType)
{
}

AbstractTank::~AbstractTank() {}

void to_json(nlohmann::json& j, const AbstractTank& tank) {}

void from_json(const nlohmann::json& j, AbstractTank& tank) {}