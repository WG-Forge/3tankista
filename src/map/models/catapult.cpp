#include "catapult.h"

void to_json(nlohmann::json& j, const Catapult& m)
{
    j = nlohmann::json{ "" };
}

void from_json(const nlohmann::json& j, Catapult& m) {}
