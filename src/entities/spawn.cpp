#include "spawn.h"

#include "render_utility/default_material.h"
#include "render_utility/material_generator.h"
#include "render_utility/round_shape.h"
#include "render_utility/shape_generator.h"

#include "components/shape_component.h"

Spawn::Spawn(const ecs::EntityId&   entityId,
             ecs::ComponentManager* componentManager,
             const Vector3i&        position,
             const Color&           color)
    : GameObject<Spawn>(entityId, componentManager)
{
    Shape shape = ShapeGenerator::CreateShape<RoundShape>();

    this->AddComponent<ShapeComponent>(shape);

    this->transform = this->AddComponent<TransformComponent>(position);

    this->material = this->AddComponent<MaterialComponent>(
        MaterialGenerator::CreateMaterial<DefaultMaterial>(), color);
}
