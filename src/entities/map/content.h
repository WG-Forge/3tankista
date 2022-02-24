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
    auto&       GetBase() { return this->base; }
    const auto& GetBase() const { return this->base; }

    void        SetObstacle(std::vector<GameObjectId> obstacle) { this->obstacle = std::move(obstacle); }
    auto&       GetObstacle() { return this->obstacle; }
    const auto& GetObstacle() const { return this->obstacle; }

    void        SetLightRepair(std::vector<GameObjectId> lightRepair) { this->lightRepair = std::move(lightRepair); }
    auto&       GetLightRepair() { return this->lightRepair; }
    const auto& GetLightRepair() const { return this->lightRepair; }

    void        SetHardRepair(std::vector<GameObjectId> hardRepair) { this->hardRepair = std::move(hardRepair); }
    auto&       GetHardRepair() { return this->hardRepair; }
    const auto& GetHardRepair() const { return this->hardRepair; }

    void        SetCatapult(std::vector<GameObjectId> catapult) { this->catapult = std::move(catapult); }
    auto&       GetCatapult() { return this->catapult; }
    const auto& GetCatapult() const { return this->catapult; }

private:
    std::vector<GameObjectId> base;
    std::vector<GameObjectId> obstacle;
    std::vector<GameObjectId> lightRepair;
    std::vector<GameObjectId> hardRepair;
    std::vector<GameObjectId> catapult;
};
