#ifndef BASE_H
#define BASE_H

#include "matrix.hpp"

#include "nlohmann/json.hpp"

struct Base
{
};

void to_json(nlohmann::json& j, const Base& m);

void from_json(const nlohmann::json& j, Base& m);

#endif // BASE_H
