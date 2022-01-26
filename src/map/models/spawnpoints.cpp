#include "spawnpoints.h"
#include "enumparser.h"
#include "singleton.h"

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
            std::vector<Vector3i> spawnPoints;
            j.at(key).get_to<std::vector<Vector3i>>(spawnPoints);
            m.GetTanksSpawnPoints().emplace_back(
                std::make_pair<TankType, std::vector<Vector3i>>(
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
