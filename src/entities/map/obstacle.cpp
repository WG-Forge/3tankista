#include "obstacle.h"
#include "components/shape_component.h"
#include "render/materials/default_material.h"
#include "render/materials/material_generator.h"
#include "render/shapes/hex_shape.h"
#include "render/shapes/shape_generator.h"

Obstacle::Obstacle(const ecs::EntityId& entityId, ecs::ComponentManager* componentManager, const Vector3i& position)
    : GameObject<Obstacle>(entityId, componentManager)
{
    Shape shape = ShapeGenerator::CreateShape<HexShape>(1);

    this->AddComponent<ShapeComponent>(shape);

    this->transform = this->AddComponent<TransformComponent>(position);

    this->material   = this->AddComponent<MaterialComponent>(MaterialGenerator::CreateMaterial<DefaultMaterial>(),
                                                           Color{ 0.2f, 0.2f, 0.2f, 1.0f });
}