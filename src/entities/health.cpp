#include "health.h"

#include "components/shape_component.h"

#include "render/materials/default_material.h"
#include "render/materials/material_generator.h"

#include "render/shapes/quad_shape.h"
#include "render/shapes/shape_generator.h"

Health::Health(const ecs::EntityId&   entityId,
               ecs::ComponentManager* componentManager,
               const Vector3i&        position,
               const std::string&     textureFileName)
    : GameObject<Health>(entityId, componentManager)
{
    Shape shape = ShapeGenerator::CreateShape<QuadShape>();

    this->AddComponent<ShapeComponent>(shape);

    this->transformComponent = AddComponent<TransformComponent>(position);

    this->textureComponent  = this->AddComponent<TextureComponent>(textureFileName);
    this->materialComponent = this->AddComponent<MaterialComponent>(
        MaterialGenerator::CreateMaterial<DefaultMaterial>(), Color{ 1.0f, 1.0f, 1.0f, 1.0f });
}
