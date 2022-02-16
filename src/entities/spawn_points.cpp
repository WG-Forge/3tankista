#include "spawn_points.h"

SpawnPoints::SpawnPoints(const ecs::EntityId&   entityId,
                         ecs::ComponentManager* componentManager)
    : GameObject<SpawnPoints>(entityId, componentManager)
{
    this->tankTypeSpawnComponents.emplace_back(
        AddComponent<TankTypeComponent>(TankType::NO_TYPE),
        std::vector<SpawnPositionComponent*>{
            AddComponent<SpawnPositionComponent>(Vector3i{ 0, 0, 0 }) });
}

void SpawnPoints::SetModel(const SpawnPointsModel& model)
{
    this->tankTypeSpawnComponents.clear();
    for (auto& pair : model.spawnPoints)
    {
        std::vector<SpawnPositionComponent*> spawnPositionVector;
        for (auto& spawnPosition : pair.second)
        {
            spawnPositionVector.emplace_back(
                AddComponent<SpawnPositionComponent>(spawnPosition));
        }
        this->tankTypeSpawnComponents.emplace_back(
            AddComponent<TankTypeComponent>(pair.first), spawnPositionVector);
    }
}
