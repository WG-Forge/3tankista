#include "health_bar.h"

#include "systems/render_system.h"

HealthBar::HealthBar(const ecs::EntityId&   entityId,
                     ecs::ComponentManager* componentManager,
                     const uint64_t         vehicleId,
                     const Matrix4f&        transform,
                     const std::string&     healthTextureFileName,
                     const std::string&     healthText,
                     const std::string&     tankTextureFileName,
                     const Color&           spawnColor)
    : ecs::Entity<HealthBar>(entityId, componentManager)
{

    this->vehicleId = vehicleId;

    this->tankEntityId =
        ecs::ecsEngine->GetEntityManager()->CreateEntity<Health>(Vector3i(0, 0, 0), tankTextureFileName);
    Health* tank = (Health*)ecs::ecsEngine->GetEntityManager()->GetEntity(this->tankEntityId);

    static const auto aspectRatio = GAME_WINDOW_WIDTH / 1920.0f;

    tank->GetComponent<TransformComponent>()->SetTransform(
        Matrix4f{ { 3.5f * aspectRatio * transform[0], transform[1], transform[2], transform[3] },
                  { transform[4], 1.96875f * aspectRatio * transform[5], transform[6], transform[7] },
                  { transform[8], transform[9], transform[10], transform[11] },
                  { transform[12], transform[13], transform[14], transform[15] } });

    this->healthEntityId =
        ecs::ecsEngine->GetEntityManager()->CreateEntity<Health>(Vector3i(0, 0, 0), healthTextureFileName);
    Health* atSpgFirstPlayerHp = (Health*)ecs::ecsEngine->GetEntityManager()->GetEntity(this->healthEntityId);

    // NOTE: it's magic numbers only for beautiful image
    TransformComponent* atSpgFirstPlayerHpTransformComponent = atSpgFirstPlayerHp->GetComponent<TransformComponent>();
    atSpgFirstPlayerHpTransformComponent->SetTransform(
        Matrix4f{ { 15 * aspectRatio * transform[0],
                    transform[1],
                    transform[2],
                    transform[3] + (transform[3] > 0 ? -0.14f * aspectRatio * GAME_WINDOW_WIDTH / 2.0f
                                                     : 0.14f * aspectRatio * GAME_WINDOW_WIDTH / 2.0f) },
                  { transform[4],
                    7 * aspectRatio * transform[5],
                    transform[6],
                    transform[7] + 0.002f * aspectRatio * GAME_WINDOW_HEIGHT },
                  { transform[8], transform[9], transform[10], transform[11] },
                  { transform[12], transform[13], transform[14], transform[15] } });

    ecs::ecsEngine->GetSystemManager()->GetSystem<RenderSystem>()->DrawText(
        vehicleId,
        healthText,
        Vector2f{ transform[3] + (transform[3] > 0 ? -0.12f * aspectRatio * GAME_WINDOW_WIDTH / 2.0f
                                                   : 0.12f * aspectRatio * GAME_WINDOW_WIDTH / 2.0f),
                  transform[7] - 0.021f * aspectRatio * GAME_WINDOW_HEIGHT / 2.0f },
        1.0 * aspectRatio,
        Color(9.0f, 9.0f, 9.0f, 1.0f));
}

void HealthBar::SetHealth(const std::string& health)
{
    ecs::ecsEngine->GetSystemManager()->GetSystem<RenderSystem>()->ChangeText(vehicleId, health);
}
