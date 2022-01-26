#include "abstracttank.h"

#include "enumparser.h"
#include "singleton.h"
#include "tankfactory.h"

AbstractTank::AbstractTank(int vehicleId, const TankType& tankType)
    : vehicleId(vehicleId)
    , playerId()
    , tankType(tankType)
    , position()
    , spawnPosition()
    , health()
    , maxHealth()
    , speed()
    , damage()
    , destructionPoints()
    , capturePoints()
{
}

AbstractTank::~AbstractTank() {}

AbstractTank* nlohmann::adl_serializer<AbstractTank*>::from_json(const json& j)
{
    AbstractTank* tank         = nullptr;
    const auto&   jsonTankInfo = j.begin().value();
    TankType      tankType     = SINGLETON(EnumParser<TankType>)
                            ->String2Enum(jsonTankInfo.at("vehicle_type"));
    switch (tankType)
    {
        case TankType::LIGHT:
        {
            break;
        }
        case TankType::MEDIUM:
        {
            tank = SINGLETON(TankFactory)
                       ->CreateMediumTank(std::stoi(j.begin().key()));
            break;
        }
        case TankType::HEAVY:
        {
            break;
        }
        case TankType::AT_SPG:
        {
            break;
        }
        case TankType::SPG:
        {
            break;
        }
        default:
        {
            return tank;
        }
    }

    jsonTankInfo.at("player_id").get_to<int>(tank->GetPlayerId());
    jsonTankInfo.at("health").get_to<int>(tank->GetHealth());
    jsonTankInfo.at("spawn_position")
        .get_to<Vector3i>(tank->GetSpawnPosition());
    jsonTankInfo.at("position").get_to<Vector3i>(tank->GetPosition());
    jsonTankInfo.at("capture_points").get_to<int>(tank->GetCapturePoints());
    return tank;
}
void nlohmann::adl_serializer<AbstractTank*>::to_json(nlohmann::json& j,
                                                      AbstractTank*   t)
{
}
