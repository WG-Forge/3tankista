#include "content.h"

Content::Content(const ecs::EntityId& entityId, ecs::ComponentManager* componentManager)
    : GameObject<Content>(entityId, componentManager)
{
}