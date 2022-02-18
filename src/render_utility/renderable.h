#pragma once

#include "renderable_group.h"

#include "game/game_types.h"

#include "components/material_component.h"
#include "components/shape_component.h"
#include "components/transform_component.h"

#include "ecs.h"

#include <list>
#include <unordered_map>

struct Renderable
{
    GameObjectId  gameObjectId;
    ecs::IEntity* gameObject;

    TransformComponent* transform;
    MaterialComponent*  material;
    ShapeComponent*     shape;

    Renderable(ecs::IEntity*       entity,
               TransformComponent* position,
               MaterialComponent*  material,
               ShapeComponent*     shape)
        : gameObjectId(entity->GetEntityID())
        , gameObject(entity)
        , transform(position)
        , material(material)
        , shape(shape)
    {
    }

    ~Renderable()
    {
        this->gameObjectId = INVALID_GAMEOBJECT_ID;
        this->gameObject   = nullptr;
        this->transform    = nullptr;
        this->material     = nullptr;
        this->shape        = nullptr;
    }
};

using RenderableList   = std::list<Renderable>;
using RenderableGroups = std::unordered_map<RenderableGroup, RenderableList>;
