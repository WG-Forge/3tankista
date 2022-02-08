#pragma once

#include "game_events.h"

template <typename T>
class GameObject : public ecs::Entity<T>
{
public:
    GameObject()
    {
        ecs::Ecs_Engine->SendEvent<GameObjectCreated>(
            this->GetEntityID(), this->GetStaticEntityTypeID());
    }

    virtual ~GameObject()
    {
        ecs::Ecs_Engine->SendEvent<GameObjectDestroyed>(
            this->GetEntityID(), this->GetStaticEntityTypeID());
    }
};
