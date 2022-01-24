#ifndef REPAIR_H
#define REPAIR_H

#include "nlohmann/json.hpp"

struct Repair
{
    enum class RepairPower
    {
        Light,
        Hard
    };

public:
    Repair();

public:
    void        SetPower(const RepairPower& power) { this->power = power; }
    auto&       GetPower() { return this->power; }
    const auto& GetPower() const { return this->power; }

private:
    RepairPower power;
};

void to_json(nlohmann::json& j, const Repair& m);

void from_json(const nlohmann::json& j, Repair& m);

#endif // REPAIR_H
