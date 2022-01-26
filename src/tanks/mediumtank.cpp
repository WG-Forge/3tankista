#include "mediumtank.h"

MediumTank::MediumTank(int vehicleId)
    : AbstractTank(vehicleId, TankType::MEDIUM)
{
    SetHealth(2);
    SetMaxHealth(2);
    SetSpeed(2);
    SetDamage(1);
    SetDestructionPoints(2);
}

MediumTank::~MediumTank() {}

bool MediumTank::CanShoot(const Vector3i& point) const
{
    return false;
}

bool MediumTank::CanMove(const Vector3i& point) const
{
    return false;
}
void to_json(nlohmann::json& j, const MediumTank& tank) {}

void from_json(const nlohmann::json& j, MediumTank& tank) {}