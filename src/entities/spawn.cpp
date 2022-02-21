#include "spawn.h"

#include "components/shape_component.h"

#include "render/materials/default_material.h"
#include "render/materials/material_generator.h"

#include "render/shapes/round_shape.h"
#include "render/shapes/shape_generator.h"

Spawn::Spawn(const ecs::EntityId&   entityId,
             ecs::ComponentManager* componentManager,
             const Vector3i&        position,
             const Color&           color)
    : GameObject<Spawn>(entityId, componentManager)
{
    Shape shape = ShapeGenerator::CreateShape<RoundShape>();

    this->AddComponent<ShapeComponent>(shape);

    this->transform = this->AddComponent<TransformComponent>(position);

    this->material = this->AddComponent<MaterialComponent>(MaterialGenerator::CreateMaterial<DefaultMaterial>(), color);
}
