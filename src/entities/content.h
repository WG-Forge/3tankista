#pragma once

#include "base.h"
#include "game/game_object.h"
#include "obstacle.h"

class Content : public GameObject<Content>
{
public:
    Content(const ecs::EntityId&   entityId,
            ecs::ComponentManager* componentManager);
    ~Content() override = default;

    void SetBase(std::vector<GameObjectId> base)
    {
        this->base = std::move(base);
    }
    auto&       GetBase() { return this->base; }
    const auto& GetBase() const { return this->base; }

    void SetObstacle(std::vector<GameObjectId> obstacle)
    {
        this->base = std::move(base);
    }
    auto&       GetObstacle() { return this->obstacle; }
    const auto& GetObstacle() const { return this->obstacle; }

private:
    std::vector<GameObjectId> base;
    std::vector<GameObjectId> obstacle;
};
