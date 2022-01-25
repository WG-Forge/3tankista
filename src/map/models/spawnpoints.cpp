#include "spawnpoints.h"

#include "singleton.h"

template <>
EnumParser<TankType>::EnumParser()
{
    enumMap["light_tank"]  = TankType::LIGHT;
    enumMap["medium_tank"] = TankType::MEDIUM;
    enumMap["heavy_tank"]  = TankType::HEAVY;
    enumMap["at_spg_tank"] = TankType::AT_SPG;
    enumMap["spg_tank"]    = TankType::SPG;
}

SpawnPoints::SpawnPoints()
/*: mediumTankSpawnPoints()*/ {}

void to_json(nlohmann::json& j, const SpawnPoints& m)
{
    j = nlohmann::json{ "" };
}

void from_json(const nlohmann::json& j, SpawnPoints& m)
{
    try
    {
        for (const auto& [key, value] : j.items())
        {
            std::vector<Vector3d> spawnPoints;
            j.at(key).get_to<std::vector<Vector3d>>(spawnPoints);
            m.GetTanksSpawnPoints().emplace_back(
                std::make_pair<TankType, std::vector<Vector3d>>(
                    SINGLETON(EnumParser<TankType>)->String2Enum(key),
                    std::move(spawnPoints)));
        }
    }
    catch (nlohmann::json::type_error& e)
    {
        std::cout << e.what() << std::endl << std::flush;
    }
    catch (nlohmann::json::out_of_range& e)
    {
        std::cout << e.what() << std::endl << std::flush;
    }
    catch (nlohmann::json::parse_error& e)
    {
        std::cout << e.what() << std::endl << std::flush;
    }
}
