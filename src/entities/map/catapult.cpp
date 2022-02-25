#include "catapult.h"

#include "render/materials/default_material.h"
#include "render/shapes/quad_shape.h"

Catapult::Catapult(const ecs::EntityId& entityId, ecs::ComponentManager* componentManager, const Vector3i& position)
    : GameObject<Catapult>(entityId, componentManager)
{
    Shape shape = ShapeGenerator::CreateShape<QuadShape>();

    this->AddComponent<ShapeComponent>(shape);

    this->transform = this->AddComponent<TransformComponent>(position);
    this->transform->GetTransform().SetScale(Vector3f{ 2.0f, 1.5f, 1.0f });
    this->material         = this->AddComponent<MaterialComponent>(MaterialGenerator::CreateMaterial<DefaultMaterial>(),
                                                           Color(1.0f, 1.0f, 1.0f, 1.0f));
    this->textureComponent = this->AddComponent<TextureComponent>(CATAPULT_TEXTURE_NAME);
    this->usage            = this->AddComponent<UsageComponent>(0);
}
