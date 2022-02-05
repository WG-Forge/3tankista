#include "tank_types.h"
#include "utility/enum_parser.h"

template <>
EnumParser<TankType>::EnumParser()
{
    enumMap["light_tank"]  = TankType::LIGHT;
    enumMap["medium_tank"] = TankType::MEDIUM;
    enumMap["heavy_tank"]  = TankType::HEAVY;
    enumMap["at_spg"]      = TankType::AT_SPG;
    enumMap["spg"]         = TankType::SPG;
}
