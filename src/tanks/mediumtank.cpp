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

void from_json(const nlohmann::json& j, MediumTank& tank)
{
    j.at("capture_points").get_to<int>(tank.GetCapturePoints());
    j.at("health").get_to<int>(tank.GetHealth());
    std::vector<int> temp;
    for (const auto& [coord, c_value] : j["position"].items())
    {
        temp.emplace_back(c_value);
    }
    Vector3i pos = { temp[0], temp[1], temp[2] };
    temp.clear();
    for (const auto& [coord, c_value] : j["spawn_position"].items())
    {
        temp.emplace_back(c_value);
    }
    Vector3i spos = { temp[0], temp[1], temp[2] };
    tank.SetPosition(pos);
    tank.SetSpawnPosition(spos);
}