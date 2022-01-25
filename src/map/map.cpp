#include "map.h"

Map::Map()
    : size()
    , name()
    , spawnPoints()
    , content()
{
}

void to_json(nlohmann::json& j, const Map& m) {}

void from_json(const nlohmann::json& j, Map& m)
{
    j.at("size").get_to<std::size_t>(m.GetSize());
    j.at("name").get_to<std::string>(m.GetName());
    j.at("spawn_points").get_to<std::vector<SpawnPoints>>(m.GetSpawnPoints());
    j.at("content").get_to<Content>(m.GetContent());
}
