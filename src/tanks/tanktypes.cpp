#include "tanktypes.h"
#include "enumparser.h"

template <>
EnumParser<TankType>::EnumParser()
{
    enumMap["light_tank"]  = TankType::LIGHT;
    enumMap["medium_tank"] = TankType::MEDIUM;
    enumMap["heavy_tank"]  = TankType::HEAVY;
    enumMap["at_spg_tank"] = TankType::AT_SPG;
    enumMap["spg_tank"]    = TankType::SPG;
}
