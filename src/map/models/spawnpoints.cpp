#include "spawnpoints.h"

SpawnPoints::SpawnPoints()
    : mediumTankSpawnPoints()
{
}

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
            if (key == "light_tank")
            {
                j.at(key).get_to<std::vector<LightTankSpawnPoint>>(
                    m.GetLightTankSpawnPoints());
            }
            else if (key == "medium_tank")
            {
                j.at(key).get_to<std::vector<MediumTankSpawnPoint>>(
                    m.GetMediumTankSpawnPoints());
            }
            else if (key == "heavy_tank")
            {
                j.at(key).get_to<std::vector<HeavyTankSpawnPoint>>(
                    m.GetHeavyTankSpawnPoints());
            }
            else if (key == "at_spg_tank")
            {
                j.at(key).get_to<std::vector<AtSpgTankSpawnPoint>>(
                    m.GetAtSpgTankSpawnPoints());
            }
            else if (key == "spg_tank")
            {
                j.at(key).get_to<std::vector<SpgTankSpawnPoint>>(
                    m.GetSpgTankSpawnPoints());
            }
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
