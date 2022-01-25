#include "abstracttank.h"

AbstractTank::AbstractTank(int vehicleId, Player *owner, const TankType& tankType)
    : vehicleId(vehicleId)
    , player(owner)
    , tankType(tankType)
{
}

AbstractTank::~AbstractTank()
{
}

void to_json(nlohmann::json& j, const AbstractTank& tank) {}

void from_json(const nlohmann::json& j, AbstractTank& tank)
{
    // TODO: Parse json
}
