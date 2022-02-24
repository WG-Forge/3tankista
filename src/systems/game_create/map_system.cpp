#include "map_system.h"
#include "entities/map/catapult.h"
#include "entities/map/hard_repair.h"
#include "entities/map/light_repair.h"

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
    auto mapEntityId      = entityManager->CreateEntity<Map>(event->mapModel.size, event->mapModel.name);
    auto mapIEntity       = entityManager->GetEntity(mapEntityId);

    auto map     = dynamic_cast<Map*>(entityManager->GetEntity(mapEntityId));
    auto content = dynamic_cast<Content*>(entityManager->GetEntity(map->GetContent()));

    auto world = entityManager->GetEntity(componentManager->begin<TurnComponent>()->GetOwner());
    world->GetComponent<HexMapComponent>()->SetSize(map->GetComponent<SizeComponent>()->GetSize());

    // creating base entities
    auto                      baseVectorV3i = event->mapModel.base;
    std::vector<GameObjectId> baseVectorId;
    for (auto& base : baseVectorV3i)
    {
        auto tempBaseId = entityManager->CreateEntity<Base>(base);
        baseVectorId.emplace_back(tempBaseId);
    }
    content->SetBase(baseVectorId);

    // creating obstacle entities
    auto                      obstacleVectorV3i = event->mapModel.obstacle;
    std::vector<GameObjectId> obstacleVectorId;
    for (auto& obstacle : obstacleVectorV3i)
    {
        auto tempObstacleId = entityManager->CreateEntity<Obstacle>(obstacle);
        GameplaySystem::SetHexMapComponentCell(world->GetComponent<HexMapComponent>(), obstacle, CellState::OBSTACLE);
        obstacleVectorId.emplace_back(tempObstacleId);
    }
    content->SetObstacle(obstacleVectorId);

    // creating lightRepair entities
    auto                      lightRepairVectorV3i = event->mapModel.lightRepair;
    std::vector<GameObjectId> lightRepairVectorId;
    for (auto& lightRepair : lightRepairVectorV3i)
    {
        auto tempLightRepair =
            entityManager->CreateEntity<LightRepair>(lightRepair);
        lightRepairVectorId.emplace_back(tempLightRepair);
    }
    content->SetLightRepair(lightRepairVectorId);

    // creating hardRepair entities
    auto                      hardRepairVectorV3i = event->mapModel.hardRepair;
    std::vector<GameObjectId> hardRepairVectorId;
    for (auto& hardRepair : hardRepairVectorV3i)
    {
        //purple color
        auto temphardRepair = entityManager->CreateEntity<HardRepair>(hardRepair);
        hardRepairVectorId.emplace_back(temphardRepair);
    }
    content->SetHardRepair(hardRepairVectorId);

    // creating catapult entities
    auto                      catapultVectorV3i = event->mapModel.catapult;
    std::vector<GameObjectId> catapultVectorId;
    for (auto& catapult : catapultVectorV3i)
    {
        //orange color
        auto tempcatapult = entityManager->CreateEntity<Catapult>(catapult);
        catapultVectorId.emplace_back(tempcatapult);
    }
    content->SetCatapult(catapultVectorId);

    // creating spawnPoints entities
    std::vector<GameObjectId> spawnPoints;
    for (const auto& mapSpawnPoint : event->mapModel.mapSpawnPoints)
    {
        auto spawnPointsId = entityManager->CreateEntity<SpawnPoints>();
        auto spawnEntity   = dynamic_cast<SpawnPoints*>(entityManager->GetEntity(spawnPointsId));
        spawnEntity->SetModel(mapSpawnPoint);
        spawnPoints.emplace_back(spawnPointsId);
    }

    map->SetSpawnPoints(spawnPoints);
}

void MapSystem::RegisterEventCallbacks()
{
    RegisterEventCallback(&MapSystem::OnMapResponse);
}

void MapSystem::UnregisterEventCallbacks()
{
    UnregisterEventCallback(&MapSystem::OnMapResponse);
}
