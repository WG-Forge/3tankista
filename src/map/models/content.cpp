#include "content.h"

Content::Content()
    : base()
    , catapult()
    , lightRepair()
    , hardRepair()
    , obstacle()
{
}

void to_json(nlohmann::json& j, const Content& m)
{
    j = nlohmann::json{ "" };
}

void from_json(const nlohmann::json& j, Content& m)
{
    try
    {
        for (const auto& [key, value] : j.items())
        {
            if (key == "base")
            {
                j.at(key).get_to<std::vector<Vector3d>>(m.GetBase().GetHexes());
            }
            else if (key == "catapult")
            {
                // j.at("catapult").get_to<std::vector<...>>(m.GetCatapult().);
            }
            else if (key == "hard_repair")
            {
                // j.at("hard_repair").get_to<std::vector<...>>(m.GetHardRepair().);
            }
            else if (key == "light_repair")
            {
                // j.at("light_repair").get_to<std::vector<...>>(m.GetLightRepair().);
            }
            else if (key == "obstacle")
            {
                // j.at("obstacle").get_to<std::vector<...>>(m.GetObstacle().);
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
