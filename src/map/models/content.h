#ifndef CONTENT_H
#define CONTENT_H

#include <vector>

#include "base.h"
#include "catapult.h"
#include "hardrepair.h"
#include "lightrepair.h"
#include "obstacle.h"

struct Content
{
    Content();

public:
    void        SetBase(const Base& base) { this->base = base; }
    auto&       GetBase() { return this->base; }
    const auto& GetBase() const { return this->base; }

    void  SetCatapult(const Catapult& catapult) { this->catapult = catapult; }
    auto& GetCatapult() { return this->catapult; }
    const auto& GetCatapult() const { return this->catapult; }

    void SetLightRepair(const LightRepair& lightRepair)
    {
        this->lightRepair = lightRepair;
    }
    auto&       GetLightRepair() { return this->lightRepair; }
    const auto& GetLightRepair() const { return this->lightRepair; }

    void SetHardRepair(const HardRepair& hardRepair)
    {
        this->hardRepair = hardRepair;
    }
    auto&       GetHardRepair() { return this->hardRepair; }
    const auto& GetHardRepair() const { return this->hardRepair; }

    void  SetObstacle(const Obstacle& obstacle) { this->obstacle = obstacle; }
    auto& GetObstacle() { return this->obstacle; }
    const auto& GetObstacle() const { return this->obstacle; }

private:
    Base        base;
    Catapult    catapult;
    LightRepair lightRepair;
    HardRepair  hardRepair;
    Obstacle    obstacle;
};

void to_json(nlohmann::json& json, const Content& content);

void from_json(const nlohmann::json& json, Content& content);

#endif // CONTENT_H
