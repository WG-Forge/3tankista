#pragma once

#include "catapult.h"
#include "hard_repair.h"
#include "light_repair.h"
#include "obstacle.h"
#include <vector>

struct Content
{
    Content() = default;

public:
    void  SetBase(std::vector<Vector3i>& base) { this->base = std::move(base); }
    auto& GetBase() { return this->base; }
    const auto& GetBase() const { return this->base; }

    void SetCatapult(Catapult& catapult)
    {
        this->catapult = std::move(catapult);
    }
    auto&       GetCatapult() { return this->catapult; }
    const auto& GetCatapult() const { return this->catapult; }

    void SetLightRepair(LightRepair& lightRepair)
    {
        this->lightRepair = std::move(lightRepair);
    }
    auto&       GetLightRepair() { return this->lightRepair; }
    const auto& GetLightRepair() const { return this->lightRepair; }

    void SetHardRepair(HardRepair& hardRepair)
    {
        this->hardRepair = std::move(hardRepair);
    }
    auto&       GetHardRepair() { return this->hardRepair; }
    const auto& GetHardRepair() const { return this->hardRepair; }

    void SetObstacle(Obstacle& obstacle)
    {
        this->obstacle = std::move(obstacle);
    }
    auto&       GetObstacle() { return this->obstacle; }
    const auto& GetObstacle() const { return this->obstacle; }

private:
    std::vector<Vector3i> base;
    Catapult              catapult;
    LightRepair           lightRepair;
    HardRepair            hardRepair;
    Obstacle              obstacle;
};

void to_json(nlohmann::json& json, const Content& content);

void from_json(const nlohmann::json& json, Content& content);
