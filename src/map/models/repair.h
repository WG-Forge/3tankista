#pragma once

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
    explicit Repair(RepairPower power);
    virtual ~Repair() = default;

public:
    void SetPower(RepairPower power) { this->power = power; }
    auto GetPower() const { return this->power; }

private:
    RepairPower power;
};

void to_json(nlohmann::json& json, const Repair& repair);

void from_json(const nlohmann::json& json, Repair& repair);
