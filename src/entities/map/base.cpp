#include "base.h"
#include "components/shape_component.h"
#include "render/materials/default_material.h"
#include "render/materials/material_generator.h"
#include "render/shapes/hex_shape.h"
#include "render/shapes/shape_generator.h"

Base::Base(const ecs::EntityId& entityId, ecs::ComponentManager* componentManager, const Vector3i& position)
    : GameObject<Base>(entityId, componentManager)
{
    Shape shape = ShapeGenerator::CreateShape<HexShape>(1);

    this->AddComponent<ShapeComponent>(shape);
    this->transform = this->AddComponent<TransformComponent>(position);
    this->material  = this->AddComponent<MaterialComponent>(MaterialGenerator::CreateMaterial<DefaultMaterial>(),
                                                           Color(0.55f, 0.84f, 0.56f, 1.0f));
}
