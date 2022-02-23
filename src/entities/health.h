#pragma once

#include "game/game_object.h"

#include "components/material_component.h"
#include "components/texture_component.h"
#include "components/transform_component.h"

class Health : public GameObject<Health>
{
public:
    Health(const ecs::EntityId&   entityId,
           ecs::ComponentManager* componentManager,
           const Vector3i&        position,
           const std::string&     textureFileName);
    ~Health() override = default;

private:
    TransformComponent* transformComponent;
    MaterialComponent*  materialComponent;
    TextureComponent*   textureComponent;
};
