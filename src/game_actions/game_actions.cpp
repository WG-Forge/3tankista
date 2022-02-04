#include "game_actions.h"

GameActions::GameActions() {}

void to_json(nlohmann::json& json, const GameActions& gameActions)
{
    json = nlohmann::json{ "" };
}

void from_json(const nlohmann::json& json, GameActions& gameActions)
{
    try
    {
        json.at("actions").get_to(gameActions.GetActions());
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
