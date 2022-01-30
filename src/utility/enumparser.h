#ifndef ENUMPARSER_H
#define ENUMPARSER_H

#include <iterator>
#include <map>
#include <string>

template <typename T>
class EnumParser
{
    using enum_type = T;

public:
    EnumParser();

    enum_type String2Enum(const std::string& value)
    {
        const auto& iValue = enumMap.find(value);
        if (iValue == enumMap.end())
        {
            throw std::runtime_error("");
        }
        return iValue->second;
    }

    std::string Enum2String(const enum_type& value)
    {
        bool terminateRequest = false;
        for (const auto& it : enumMap)
        {
            if (it->second == value)
            {
                return it->first;
            }
        }

        return std::string("");
    }

private:
    std::map<std::string, T> enumMap;
};

#endif // ENUMPARSER_H
