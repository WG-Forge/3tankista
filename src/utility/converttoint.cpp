#include "converttoint.h"
#include <sstream>

int ConvertToInt(const char* s)
{
    std::stringstream strValue;
    strValue << s;
    int intValue;
    strValue >> intValue;
    return intValue;
}