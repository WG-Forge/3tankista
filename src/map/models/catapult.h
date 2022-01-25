#ifndef CATAPULT_H
#define CATAPULT_H

#include "nlohmann/json.hpp"

struct Catapult
{
};

void to_json(nlohmann::json& j, const Catapult& m);

void from_json(const nlohmann::json& j, Catapult& m);

#endif // CATAPULT_H
