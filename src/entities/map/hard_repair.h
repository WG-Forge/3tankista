#pragma once

#include "components/material_component.h"
#include "components/shape_component.h"
#include "components/texture_component.h"
#include "components/transform_component.h"
#include "game/game_object.h"
#include "render/materials/default_material.h"
#include "render/materials/material_generator.h"
#include "render/shapes/hex_shape.h"
#include "render/shapes/shape.h"
#include "render/shapes/shape_generator.h"

class HardRepair : public GameObject<HardRepair>
{
public:
    HardRepair(const ecs::EntityId& entityId, ecs::ComponentManager* componentManager, const Vector3i& position);
    ~HardRepair() override = default;

private:
    TransformComponent* transform;
    MaterialComponent*  material;
    TextureComponent*   textureComponent;
};
