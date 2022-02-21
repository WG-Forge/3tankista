#include "content.h"

Content::Content(const ecs::EntityId& entityId, ecs::ComponentManager* componentManager)
    : GameObject<Content>(entityId, componentManager)
{
    base.emplace_back(ecs::ecsEngine->GetEntityManager()->CreateEntity<Base>(1, Vector3i(), Color()));
    obstacle.emplace_back(ecs::ecsEngine->GetEntityManager()->CreateEntity<Obstacle>(Vector3i()));
};