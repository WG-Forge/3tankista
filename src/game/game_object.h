#pragma once

#include "game_events.h"

template <typename T>
class GameObject : public ecs::Entity<T>
{
public:
    GameObject(const ecs::EntityId&   entityId,
               ecs::ComponentManager* componentManager)
        : ecs::Entity<T>(entityId, componentManager)
    {
        ecs::ecsEngine->SendEvent<GameObjectCreated>(
            this->GetEntityID(), this->GetStaticEntityTypeID());
    }

    virtual ~GameObject()
    {
        ecs::ecsEngine->SendEvent<GameObjectDestroyed>(
            this->GetEntityID(), this->GetStaticEntityTypeID());
    }
};