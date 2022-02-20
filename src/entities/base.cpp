#include "base.h"

#include "components/shape_component.h"

#include "render/materials/default_material.h"
#include "render/materials/material_generator.h"

#include "render/shapes/hex_shape.h"
#include "render/shapes/shape_generator.h"

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
