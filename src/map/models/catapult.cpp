#include "catapult.h"

void to_json(nlohmann::json& json, const Catapult& catapult)
{
    json = nlohmann::json{ "" };
}

void from_json(const nlohmann::json& json, Catapult& catapult) {}
