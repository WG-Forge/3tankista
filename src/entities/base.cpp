#include "base.h"

#include "render_utility/default_material.h"
#include "render_utility/hex_shape.h"
#include "render_utility/line_material.h"
#include "render_utility/material_generator.h"
#include "render_utility/shape_generator.h"

#include "components/shape_component.h"

Base::Base(const ecs::EntityId&   entityId,
           ecs::ComponentManager* componentManager,
           const std::size_t      size,
           const Vector3i&        position,
           const Color&           color)
    : GameObject<Base>(entityId, componentManager)
{
    Shape shape = ShapeGenerator::CreateShape<HexShape>(size);

    this->AddComponent<ShapeComponent>(shape);

    this->transform = this->AddComponent<TransformComponent>(position);

    this->material = this->AddComponent<MaterialComponent>(
        MaterialGenerator::CreateMaterial<DefaultMaterial>(), color);
}
