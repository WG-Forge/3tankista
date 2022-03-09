#include "map_system.h"
#include "entities/map/catapult.h"
#include "entities/map/hard_repair.h"
#include "entities/map/light_repair.h"
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
    auto mapEntityId      = entityManager->CreateEntity<Map>(event->mapModel.size, event->mapModel.name);
    auto mapIEntity       = entityManager->GetEntity(mapEntityId);

    auto map     = dynamic_cast<Map*>(entityManager->GetEntity(mapEntityId));
    auto content = dynamic_cast<Content*>(entityManager->GetEntity(map->GetContent()));

    auto world           = entityManager->GetEntity(componentManager->begin<TurnComponent>()->GetOwner());
    auto hexMapComponent = world->GetComponent<HexMapComponent>();

    hexMapComponent->SetSize(map->GetComponent<SizeComponent>()->GetSize());

    // creating base entities
    auto                      baseVectorV3i = event->mapModel.base;
    std::vector<uint64_t> baseVectorId;
    for (auto& base : baseVectorV3i)
    {
        auto tempBaseId = entityManager->CreateEntity<Base>(base);
        MapUtility::AddHexMapComponentCell(hexMapComponent, base, CellState::BASE);
        baseVectorId.emplace_back(tempBaseId);
    }
    content->SetBase(baseVectorId);

    // creating obstacle entities
    auto                      obstacleVectorV3i = event->mapModel.obstacle;
    std::vector<uint64_t> obstacleVectorId;
    for (auto& obstacle : obstacleVectorV3i)
    {
        auto tempObstacleId = entityManager->CreateEntity<Obstacle>(obstacle);
        MapUtility::AddHexMapComponentCell(hexMapComponent, obstacle, CellState::OBSTACLE);
        obstacleVectorId.emplace_back(tempObstacleId);
    }
    content->SetObstacle(obstacleVectorId);

    // creating lightRepair entities
    auto                      lightRepairVectorV3i = event->mapModel.lightRepair;
    std::vector<uint64_t> lightRepairVectorId;
    for (auto& lightRepair : lightRepairVectorV3i)
    {
        auto tempLightRepair = entityManager->CreateEntity<LightRepair>(lightRepair);
        MapUtility::AddHexMapComponentCell(hexMapComponent, lightRepair, CellState::LIGHT_REPAIR);
        lightRepairVectorId.emplace_back(tempLightRepair);
    }
    content->SetLightRepair(lightRepairVectorId);

    // creating hardRepair entities
    auto                      hardRepairVectorV3i = event->mapModel.hardRepair;
    std::vector<uint64_t> hardRepairVectorId;
    for (auto& hardRepair : hardRepairVectorV3i)
    {
        // purple color
        auto temphardRepair = entityManager->CreateEntity<HardRepair>(hardRepair);
        MapUtility::AddHexMapComponentCell(hexMapComponent, hardRepair, CellState::HARD_REPAIR);
        hardRepairVectorId.emplace_back(temphardRepair);
    }
    content->SetHardRepair(hardRepairVectorId);

    // creating catapult entities
    auto                      catapultVectorV3i = event->mapModel.catapult;
    std::vector<uint64_t> catapultVectorId;
    for (auto& catapult : catapultVectorV3i)
    {
        // orange color
        auto tempcatapult = entityManager->CreateEntity<Catapult>(catapult);
        MapUtility::AddHexMapComponentCell(hexMapComponent, catapult, CellState::CATAPULT);
        catapultVectorId.emplace_back(tempcatapult);
    }
    content->SetCatapult(catapultVectorId);

    // creating spawnPoints entities
    std::vector<uint64_t> spawnPoints;
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
