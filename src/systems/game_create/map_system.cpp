#include "map_system.h"
#include "utility/map_utility.h"

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
    auto entityManager    = ecs::ecsEngine->GetEntityManager();
    auto componentManager = ecs::ecsEngine->GetComponentManager();
    auto mapEntityId      = entityManager->CreateEntity<Map>(event->mapModel.size);
    auto mapIEntity       = entityManager->GetEntity(mapEntityId);

    mapIEntity->GetComponent<NameComponent>()->SetName(event->mapModel.name);

    auto map     = dynamic_cast<Map*>(entityManager->GetEntity(mapEntityId));
    auto content = dynamic_cast<Content*>(entityManager->GetEntity(map->GetContent()));

    auto                      baseVectorV3i = event->mapModel.base;
    std::vector<GameObjectId> baseVectorId;
    for (auto& base : baseVectorV3i)
    {
        auto tempBaseId = entityManager->CreateEntity<Base>(1, base, Color(0.55f, 0.84f, 0.56f, 1.0f));
        //        entityManager->GetEntity(tempBaseId)->GetComponent<TransformComponent>()->SetPosition(base);
        baseVectorId.emplace_back(tempBaseId);
    }
    content->SetBase(baseVectorId);

    auto                      obstacleVectorV3i = event->mapModel.obstacle;
    std::vector<GameObjectId> obstacleVectorId;
    for (auto& obstacle : obstacleVectorV3i)
    {
        auto tempObstacleId = entityManager->CreateEntity<Obstacle>(obstacle);
        //        entityManager->GetEntity(tempObstacleId)->GetComponent<TransformComponent>()->SetPosition(obstacle);
        obstacleVectorId.emplace_back(tempObstacleId);
    }
    content->SetObstacle(obstacleVectorId);

    std::vector<GameObjectId> spawnPoints;
    for (const auto& mapSpawnPoint : event->mapModel.mapSpawnPoints)
    {
        auto spawnPointsId = entityManager->CreateEntity<SpawnPoints>();
        auto spawnEntity   = dynamic_cast<SpawnPoints*>(entityManager->GetEntity(spawnPointsId));
        spawnEntity->SetModel(mapSpawnPoint);
        spawnPoints.emplace_back(spawnPointsId);
    }

    map->SetSpawnPoints(spawnPoints);
    auto world = entityManager->GetEntity(componentManager->begin<TurnComponent>()->GetOwner());
    world->GetComponent<HexMapComponent>()->SetSize(map->GetComponent<SizeComponent>()->GetSize());
    for (auto it = componentManager->begin<ObstacleIdComponent>(); componentManager->end<ObstacleIdComponent>() != it;
         ++it)
    {
        MapUtility::SetHexMapComponentCell(
            world->GetComponent<HexMapComponent>(),
            entityManager->GetEntity(it->GetOwner())->GetComponent<TransformComponent>()->GetPosition(),
            CellState::OBSTACLE);
    }
}

void MapSystem::RegisterEventCallbacks()
{
    RegisterEventCallback(&MapSystem::OnMapResponse);
}

void MapSystem::UnregisterEventCallbacks()
{
    UnregisterEventCallback(&MapSystem::OnMapResponse);
}
