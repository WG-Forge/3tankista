#include "map.h"

Map::Map()
    : size()
    , name()
    , spawnPoints()
    , content()
{
}

void to_json(nlohmann::json& json, const Map& map)
{
    json = nlohmann::json{ "" };
}

void from_json(const nlohmann::json& json, Map& map)
{
    try
    {
        json.at("size").get_to<std::size_t>(map.GetSize());
        json.at("name").get_to<std::string>(map.GetName());
        json.at("spawn_points")
            .get_to<std::vector<SpawnPoints>>(map.GetSpawnPoints());
        json.at("content").get_to<Content>(map.GetContent());
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
}