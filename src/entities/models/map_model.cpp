#include "map_model.h"



void to_json(nlohmann::json& json, const MapModel& mapModel)
{
    json = nlohmann::json{ "" };
}

void from_json(const nlohmann::json& json, MapModel& mapModel)
{
    try
    {
        mapModel.size = json.at("size");
        json.at("name").get_to<std::string>(mapModel.name);
        nlohmann::json jsonContent = json.at("content");
        jsonContent.at("base").get_to<std::vector<Vector3i>>(mapModel.base);
        jsonContent.at("obstacle")
            .get_to<std::vector<Vector3i>>(mapModel.obstacle);
        json.at("spawn_points").get_to<std::vector<SpawnPointsModel>>(mapModel.mapSpawnPoints);
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
