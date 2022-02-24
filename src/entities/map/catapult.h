#pragma once

#include "components/catapult_id_component.h"
#include "components/material_component.h"
#include "components/shape_component.h"
#include "components/transform_component.h"
#include "game/game_object.h"
#include "render/materials/default_material.h"
#include "render/materials/material_generator.h"
#include "render/shapes/hex_shape.h"
#include "render/shapes/shape.h"
#include "render/shapes/shape_generator.h"

class Catapult : public GameObject<Catapult>
{
public:
    Catapult(const ecs::EntityId&   entityId,
             ecs::ComponentManager* componentManager,
             const std::size_t      size,
             const Vector3i&        position,
             const Color&           color);
    ~Catapult() override = default;

private:
    CatapultIdComponent* catapultId;
    TransformComponent*  transform;
    MaterialComponent*   material;
};