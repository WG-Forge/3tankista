#pragma once

#include "nlohmann/json.hpp"

struct Catapult
{
};

void to_json(nlohmann::json& json, const Catapult& catapult);

void from_json(const nlohmann::json& json, Catapult& catapult);
