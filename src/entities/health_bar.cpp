#include "health_bar.h"

#include "systems/render_system.h"

HealthBar::HealthBar(const ecs::EntityId&   entityId,
                     ecs::ComponentManager* componentManager,
                     const Matrix4f&        transform,
                     const std::string&     healthTextureFileName,
                     const std::string&     healthText,
                     const std::string&     tankTextureFileName,
                     const Color&           spawnColor)
    : ecs::Entity<HealthBar>(entityId, componentManager)
{

    this->spawnEntityId =
        ecs::ecsEngine->GetEntityManager()->CreateEntity<Spawn>(
            Vector3i{ 0, 0, 0 }, spawnColor);
    Spawn* atSpgFirstPlayerSpawn =
        (Spawn*)ecs::ecsEngine->GetEntityManager()->GetEntity(
            this->spawnEntityId);

    TransformComponent* atSpgFirstPlayerSpawnTransformComponent =
        atSpgFirstPlayerSpawn->GetComponent<TransformComponent>();
    atSpgFirstPlayerSpawnTransformComponent->SetTransform(transform);

    this->tankEntityId = ecs::ecsEngine->GetEntityManager()->CreateEntity<Tank>(
        Vector3i(0, 0, 0), tankTextureFileName);
    Tank* atSpgFirstPlayerTank =
        (Tank*)ecs::ecsEngine->GetEntityManager()->GetEntity(
            this->tankEntityId);

    TransformComponent* atSpgFirstPlayerTankTransformComponent =
        atSpgFirstPlayerTank->GetComponent<TransformComponent>();
    atSpgFirstPlayerTankTransformComponent->SetTransform(transform);

    this->healthEntityId =
        ecs::ecsEngine->GetEntityManager()->CreateEntity<Health>(
            Vector3i(0, 0, 0), healthTextureFileName);
    Health* atSpgFirstPlayerHp =
        (Health*)ecs::ecsEngine->GetEntityManager()->GetEntity(
            this->healthEntityId);

    TransformComponent* atSpgFirstPlayerHpTransformComponent =
        atSpgFirstPlayerHp->GetComponent<TransformComponent>();
    atSpgFirstPlayerHpTransformComponent->SetTransform(Matrix4f{
        { 4 * transform[0],
          transform[1],
          transform[2],
          transform[3] + (transform[3] > 0 ? -0.1f : 0.1f) },
        { transform[4], 5 * transform[5], transform[6], transform[7] + 0.01f },
        { transform[8], transform[9], transform[10], transform[11] },
        { transform[12], transform[13], transform[14], transform[15] } });

    ecs::ecsEngine->GetSystemManager()->GetSystem<RenderSystem>()->DrawText(
        healthText,
        Vector2f{ transform[3] + (transform[3] > 0 ? -0.12f : 0.08f),
                  transform[7] - 0.015f },
        2.0,
        Color(9.0f, 9.0f, 9.0f, 1.0f));
}
