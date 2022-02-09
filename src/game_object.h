#pragma once

#include "game_events.h"

template <typename T>
class GameObject : public ecs::Entity<T>
{
public:
    GameObject()
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
