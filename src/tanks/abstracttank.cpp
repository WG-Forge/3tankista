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

bool AbstractTank::operator<(const AbstractTank& tank)
{
    return this->GetTankType() < tank.GetTankType();
}

AbstractTank::~AbstractTank() {}

void nlohmann::adl_serializer<AbstractTank*>::to_json(nlohmann::json& json,
                                                      AbstractTank*   tank)
{
    json = nlohmann::json{ "" };
}

AbstractTank* nlohmann::adl_serializer<AbstractTank*>::from_json(
    const json& json)
{
    AbstractTank* tank = nullptr;
    try
    {
        const auto& jsonTankInfo = json.begin().value();
        TankType    tankType     = SINGLETON(EnumParser<TankType>)
                                ->String2Enum(jsonTankInfo.at("vehicle_type"));
        switch (tankType)
        {
            case TankType::LIGHT:
            {
                tank = SINGLETON(TankFactory)
                           ->CreateLightTank(std::stoi(json.begin().key()));
                break;
            }
            case TankType::MEDIUM:
            {
                tank = SINGLETON(TankFactory)
                           ->CreateMediumTank(std::stoi(json.begin().key()));
                break;
            }
            case TankType::HEAVY:
            {
                tank = SINGLETON(TankFactory)
                           ->CreateHeavyTank(std::stoi(json.begin().key()));
                break;
            }
            case TankType::AT_SPG:
            {
                tank = SINGLETON(TankFactory)
                           ->CreateAtSpgTank(std::stoi(json.begin().key()));
                break;
            }
            case TankType::SPG:
            {
                tank = SINGLETON(TankFactory)
                           ->CreateSpgTank(std::stoi(json.begin().key()));
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
    }
    catch (nlohmann::json::type_error& exception)
    {
        std::cout << exception.what() << std::endl << std::flush;
    }
    catch (nlohmann::json::out_of_range& exception)
    {
        std::cout << exception.what() << std::endl << std::flush;
    }
    catch (nlohmann::json::parse_error& exception)
    {
        std::cout << exception.what() << std::endl << std::flush;
    }
    catch (std::out_of_range& exception)
    {
        std::cout << exception.what() << std::endl << std::flush;
    }
    catch (std::invalid_argument& exception)
    {
        std::cout << exception.what() << std::endl << std::flush;
    }
    return tank;
}
