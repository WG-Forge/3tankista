#include "map.h"

#include "render_utility/default_material.h"
#include "render_utility/hex_shape.h"
#include "render_utility/line_material.h"
#include "render_utility/material_generator.h"
#include "render_utility/shape_generator.h"

#include "components/shape_component.h"

Map::Map(const ecs::EntityId& entityId, ecs::ComponentManager* componentManager)
    : GameObject<Map>(entityId, componentManager)
{
    Shape shape = ShapeGenerator::CreateShape<HexShape>(11, GL_LINES);

    this->AddComponent<ShapeComponent>(shape);

    this->transform = this->AddComponent<TransformComponent>();

    this->material = this->AddComponent<MaterialComponent>(
        MaterialGenerator::CreateMaterial<LineMaterial>(),
        Color{ 0.0f, 0.0f, 0.0f, 1.0f });
}
