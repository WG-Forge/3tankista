//
// Created by serge on 26.01.22.
//

#include "winpoints.h"

WinPoints::WinPoints()
    : capture()
    , kill()
{
}

void to_json(nlohmann::json& json, const WinPoints& winPoints)
{
    json = nlohmann::json{ "" };
}

void from_json(const nlohmann::json& json, WinPoints& winPoints)
{
    json.at("capture").get_to<int>(winPoints.GetCapture());
    json.at("kill").get_to<int>(winPoints.GetKill());
}
