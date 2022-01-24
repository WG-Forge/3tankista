#include "base.h"

void to_json(nlohmann::json& j, const Base& m)
{
    j = nlohmann::json{ "" };
}

void from_json(const nlohmann::json& j, Base& m) {}
