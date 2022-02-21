#include "map.h"

#include "components/shape_component.h"

#include "render/materials/default_material.h"
#include "render/materials/material_generator.h"

#include "render/shapes/hex_shape.h"
#include "render/shapes/shape_generator.h"

Map::Map(const ecs::EntityId& entityId, ecs::ComponentManager* componentManager)
    : GameObject<Map>(entityId, componentManager)
{
    Shape shape = ShapeGenerator::CreateShape<HexShape>(11, GL_LINES);

    this->AddComponent<ShapeComponent>(shape);

    this->transform = this->AddComponent<TransformComponent>();

    this->material = this->AddComponent<MaterialComponent>(
        MaterialGenerator::CreateMaterial<DefaultMaterial>(),
        Color{ 0.0f, 0.0f, 0.0f, 1.0f });
}
