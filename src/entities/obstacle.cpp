#include "obstacle.h"

#include "render_utility/default_material.h"
#include "render_utility/hex_shape.h"
#include "render_utility/line_material.h"
#include "render_utility/material_generator.h"
#include "render_utility/shape_generator.h"

#include "components/shape_component.h"

Obstacle::Obstacle(const ecs::EntityId&   entityId,
                   ecs::ComponentManager* componentManager)
    : GameObject<Obstacle>(entityId, componentManager)
{
    Shape shape = ShapeGenerator::CreateShape<HexShape>(11);

    this->AddComponent<ShapeComponent>(shape);

    this->position = this->AddComponent<PositionComponent>(Vector3i{ 0, 0, 0 });

    this->material = this->AddComponent<MaterialComponent>(
        MaterialGenerator::CreateMaterial<DefaultMaterial>(),
        Color{ 0.2f, 0.2f, 0.2f, 1.0f });
}
