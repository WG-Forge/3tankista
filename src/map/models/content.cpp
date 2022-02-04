#include "content.h"

void to_json(nlohmann::json& json, const Content& content)
{
    json = nlohmann::json{ "" };
}

void from_json(const nlohmann::json& json, Content& content)
{
    json.at("base").get_to<std::vector<Vector3i>>(content.GetBase());
    // json.at("catapult").get_to<std::vector<...>>(content.GetCatapult().);
    // json.at("hard_repair").get_to<std::vector<...>>(content.GetHardRepair().);
    // json.at("light_repair").get_to<std::vector<...>>(content.GetLightRepair().);
    // json.at("obstacle").get_to<std::vector<...>>(content.GetObstacle().);
}
