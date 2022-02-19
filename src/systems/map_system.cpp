#include "map_system.h"

#include "components/hex_map_component.h"
#include "components/turn_component.h"
#include "ecs.h"
#include "entities/map/map.h"
#include "game/game_events.h"
#include <iostream>

MapSystem::MapSystem()
{
    this->RegisterEventCallbacks();
}

MapSystem::~MapSystem()
{
    this->UnregisterEventCallbacks();
}

void MapSystem::OnMapResponse(const MapResponseEvent* event)
{
    auto mapEntityId = ecs::ecsEngine->GetEntityManager()->CreateEntity<Map>();
    auto mapIEntity  = ecs::ecsEngine->GetEntityManager()->GetEntity(mapEntityId);

    mapIEntity->GetComponent<SizeComponent>()->SetSize(event->mapModel.size);
    mapIEntity->GetComponent<NameComponent>()->SetName(event->mapModel.name);

    auto map     = dynamic_cast<Map*>(ecs::ecsEngine->GetEntityManager()->GetEntity(mapEntityId));
    auto content = dynamic_cast<Content*>(ecs::ecsEngine->GetEntityManager()->GetEntity(map->GetContent()));

    auto                      baseVectorV3i = event->mapModel.base;
    std::vector<GameObjectId> baseVectorId;
    for (auto& base : baseVectorV3i)
    {
        auto tempBaseId = ecs::ecsEngine->GetEntityManager()->CreateEntity<Base>();
        ecs::ecsEngine->GetEntityManager()->GetEntity(tempBaseId)->GetComponent<PositionComponent>()->SetPosition(base);
        baseVectorId.emplace_back(tempBaseId);
    }
    content->SetBase(baseVectorId);

    auto                      obstacleVectorV3i = event->mapModel.obstacle;
    std::vector<GameObjectId> obstacleVectorId;
    for (auto& obstacle : obstacleVectorV3i)
    {
        auto tempObstacleId = ecs::ecsEngine->GetEntityManager()->CreateEntity<Obstacle>();
        ecs::ecsEngine->GetEntityManager()
            ->GetEntity(tempObstacleId)
            ->GetComponent<PositionComponent>()
            ->SetPosition(obstacle);
        obstacleVectorId.emplace_back(tempObstacleId);
    }
    content->SetObstacle(obstacleVectorId);

    std::vector<GameObjectId> spawnPoints;
    for (const auto& mapSpawnPoint : event->mapModel.mapSpawnPoints)
    {
        auto spawnPointsId = ecs::ecsEngine->GetEntityManager()->CreateEntity<SpawnPoints>();
        auto spawnEntity   = dynamic_cast<SpawnPoints*>(ecs::ecsEngine->GetEntityManager()->GetEntity(spawnPointsId));
        spawnEntity->SetModel(mapSpawnPoint);
        spawnPoints.emplace_back(spawnPointsId);
    }

    map->SetSpawnPoints(spawnPoints);
    auto world = ecs::ecsEngine->GetEntityManager()->GetEntity(
        ecs::ecsEngine->GetComponentManager()->begin<TurnComponent>()->GetOwner());
    world->GetComponent<HexMapComponent>()->SetSize(map->GetComponent<SizeComponent>()->GetSize());
}

void MapSystem::RegisterEventCallbacks()
{
    RegisterEventCallback(&MapSystem::OnMapResponse);
}

void MapSystem::UnregisterEventCallbacks()
{
    UnregisterEventCallback(&MapSystem::OnMapResponse);
}
