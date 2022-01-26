//
// Created by serge on 26.01.22.
//

#include "winpoints.h"
WinPoints::WinPoints()
    : capture()
    , kill()
{
}

int ConvertToInt(const char* s)
{
    std::stringstream strValue;
    strValue << s;
    int intValue;
    strValue >> intValue;
    return intValue;
}
void to_json(nlohmann::json& j, const WinPoints& wp) {}

void from_json(const nlohmann::json& j, WinPoints& wp)
{
    j.at("capture").get_to<int>(wp.GetCapture());
    j.at("kill").get_to<int>(wp.GetKill());
}