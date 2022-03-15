#pragma once

#include "base.h"
#include "game/game_object.h"
#include "obstacle.h"

class Content : public GameObject<Content>
{
public:
    Content(const ecs::EntityId& entityId, ecs::ComponentManager* componentManager);
    ~Content() override = default;

    void        SetBase(std::vector<uint64_t> base) { this->base = std::move(base); }
    auto&       GetVectorBaseId() { return this->base; }
    const auto& GetVectorBaseId() const { return this->base; }

    void        SetObstacle(std::vector<uint64_t> obstacle) { this->obstacle = std::move(obstacle); }
    auto&       GetVectorObstacleId() { return this->obstacle; }
    const auto& GetVectorObstacleId() const { return this->obstacle; }

    void        SetLightRepair(std::vector<uint64_t> lightRepair) { this->lightRepair = std::move(lightRepair); }
    auto&       GetVectorLightRepairId() { return this->lightRepair; }
    const auto& GetVectorLightRepairId() const { return this->lightRepair; }

    void        SetHardRepair(std::vector<uint64_t> hardRepair) { this->hardRepair = std::move(hardRepair); }
    auto&       GetVectorHardRepairId() { return this->hardRepair; }
    const auto& GetVectorHardRepairId() const { return this->hardRepair; }

    void        SetCatapult(std::vector<uint64_t> catapult) { this->catapult = std::move(catapult); }
    auto&       GetVectorCatapultId() { return this->catapult; }
    const auto& GetVectorCatapultId() const { return this->catapult; }

    std::vector<Vector3i> GetVectorV3i(std::vector<uint64_t> vectorId);

private:
    std::vector<uint64_t> base;
    std::vector<uint64_t> obstacle;
    std::vector<uint64_t> lightRepair;
    std::vector<uint64_t> hardRepair;
    std::vector<uint64_t> catapult;
};
