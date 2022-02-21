#include "map.h"

Map::Map(const ecs::EntityId& entityId, ecs::ComponentManager* componentManager)
    : GameObject<Map>(entityId, componentManager)
{
    this->content = ecs::ecsEngine->GetEntityManager()->CreateEntity<Content>();
    this->spawnPoints.emplace_back(ecs::ecsEngine->GetEntityManager()->CreateEntity<SpawnPoints>());
    this->nameComponent = AddComponent<NameComponent>(std::string{});
    this->sizeComponent = AddComponent<SizeComponent>(0);
};