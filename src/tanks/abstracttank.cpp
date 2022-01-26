#include "abstracttank.h"
#include "enumparser.h"
#include "singleton.h"
#include "tankfactory.h"
#include "converttoint.h"

AbstractTank::AbstractTank(int vehicleId, const TankType& tankType)
    : vehicleId(vehicleId)
    , tankType(tankType)
{
}

AbstractTank::~AbstractTank() {}

AbstractTank* nlohmann::adl_serializer<AbstractTank*>::from_json(const json& j)
{
    AbstractTank* tank     = nullptr;
    const auto&   tmp      = j.begin().value();
    TankType      tankType = SINGLETON(EnumParser<TankType>)
                            ->String2Enum(tmp.at("/vehicle_type"_json_pointer));
    switch (tankType)
    {
        case TankType::MEDIUM:
        {
            // TODO: Vlad pls fix... Use AbstractTankFactory instead TankFactory
            tank = SINGLETON(TankFactory)
                       ->CreateMediumTank(ConvertToInt(j.begin().key().c_str()));
            break;
        }
    }
    tmp.at("player_id").get_to<int>(tank->GetPlayerId());
    tmp.at("health").get_to<int>(tank->GetHealth());
    tmp.at("spawn_position").get_to<Vector3i>(tank->GetSpawnPosition());
    tmp.at("position").get_to<Vector3i>(tank->GetPosition());
    tmp.at("capture_points").get_to<int>(tank->GetCapturePoints());
    return tank;
}
void nlohmann::adl_serializer<AbstractTank*>::to_json(nlohmann::json& j,
                                                      AbstractTank*   t)
{
}