#ifndef CATAPULT_H
#define CATAPULT_H

#include "nlohmann/json.hpp"

struct Catapult
{
};

void to_json(nlohmann::json& json, const Catapult& catapult);

void from_json(const nlohmann::json& json, Catapult& catapult);

#endif // CATAPULT_H
