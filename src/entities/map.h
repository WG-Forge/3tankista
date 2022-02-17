#pragma once

#include "components/name_component.h"
#include "components/size_component.h"
#include "content.h"
#include "game/game_object.h"
#include "models/map_model.h"
#include "spawn_points.h"
#include <string>

class Map : public GameObject<Map>
{
public:
    Map(const ecs::EntityId& entityId, ecs::ComponentManager* componentManager);
    ~Map() override = default;

    void  SetContent(const GameObjectId& content) { this->content = content; }
    auto& GetContent() { return this->content; }
    const auto& GetContent() const { return this->content; }

    void SetSpawnPoints(const std::vector<GameObjectId>& spawnPoints)
    {
        this->spawnPoints = spawnPoints;
    }
    auto&       GetSpawnPoints() { return this->spawnPoints; }
    const auto& GetSpawnPoints() const { return this->spawnPoints; }

private:
    GameObjectId              content;
    std::vector<GameObjectId> spawnPoints;
    NameComponent*            nameComponent;
    SizeComponent*            sizeComponent;
};
