#include "content.h"

Content::Content(const ecs::EntityId&   entityId,
                 ecs::ComponentManager* componentManager)
    : GameObject<Content>(entityId, componentManager)
{
    base.emplace_back(ecs::ecsEngine->GetEntityManager()->CreateEntity<Base>());
    obstacle.emplace_back(
        ecs::ecsEngine->GetEntityManager()->CreateEntity<Obstacle>());
};