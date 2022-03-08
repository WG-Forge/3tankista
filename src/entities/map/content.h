#pragma once

#include "base.h"
#include "game/game_object.h"
#include "obstacle.h"

class Content : public GameObject<Content>
{
public:
    Content(const ecs::EntityId& entityId, ecs::ComponentManager* componentManager);
    ~Content() override = default;

    void        SetBase(std::vector<GameObjectId> base) { this->base = std::move(base); }
    auto&       GetVectorBaseId() { return this->base; }
    const auto& GetVectorBaseId() const { return this->base; }

    void        SetObstacle(std::vector<GameObjectId> obstacle) { this->obstacle = std::move(obstacle); }
    auto&       GetVectorObstacleId() { return this->obstacle; }
    const auto& GetVectorObstacleId() const { return this->obstacle; }

    void        SetLightRepair(std::vector<GameObjectId> lightRepair) { this->lightRepair = std::move(lightRepair); }
    auto&       GetVectorLightRepairId() { return this->lightRepair; }
    const auto& GetVectorLightRepairId() const { return this->lightRepair; }

    void        SetHardRepair(std::vector<GameObjectId> hardRepair) { this->hardRepair = std::move(hardRepair); }
    auto&       GetVectorHardRepairId() { return this->hardRepair; }
    const auto& GetVectorHardRepairId() const { return this->hardRepair; }

    void        SetCatapult(std::vector<GameObjectId> catapult) { this->catapult = std::move(catapult); }
    auto&       GetVectorCatapultId() { return this->catapult; }
    const auto& GetVectorCatapultId() const { return this->catapult; }

    std::vector<Vector3i> GetVectorV3i(std::vector<GameObjectId> vectorId);

private:
    std::vector<GameObjectId> base;
    std::vector<GameObjectId> obstacle;
    std::vector<GameObjectId> lightRepair;
    std::vector<GameObjectId> hardRepair;
    std::vector<GameObjectId> catapult;
};
