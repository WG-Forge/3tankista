#ifndef REPAIR_H
#define REPAIR_H

#include "nlohmann/json.hpp"

// Can be deleted in future

struct Repair
{
    enum class RepairPower
    {
        Undefined,
        Light,
        Hard
    };

public:
    Repair();
    Repair(const RepairPower power);
    virtual ~Repair() = default;

public:
    void        SetPower(const RepairPower& power) { this->power = power; }
    auto&       GetPower() { return this->power; }
    const auto& GetPower() const { return this->power; }

private:
    RepairPower power;
};

void to_json(nlohmann::json& json, const Repair& repair);

void from_json(const nlohmann::json& json, Repair& repair);

#endif // REPAIR_H
