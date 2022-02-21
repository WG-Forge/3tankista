#pragma once

#include "ecs.h"

#include "entities/health.h"
#include "entities/spawn.h"
#include "entities/tank.h"

class HealthBar : public ecs::Entity<HealthBar>
{
public:
    HealthBar(const ecs::EntityId&   entityId,
              ecs::ComponentManager* componentManager,
              const Matrix4f&        transform,
              const std::string&     healthTextureFileName,
              const std::string&     healthText,
              const std::string&     tankTextureFileName,
              const Color&           spawnColor);
    ~HealthBar() override = default;

    auto GetHealthEntity()
    {
        return ecs::ecsEngine->GetEntityManager()->GetEntity(healthEntityId);
    }
    const auto GetHealthEntity() const
    {
        return ecs::ecsEngine->GetEntityManager()->GetEntity(healthEntityId);
    }

    auto GetSpawnEntity()
    {
        return ecs::ecsEngine->GetEntityManager()->GetEntity(healthEntityId);
    }
    const auto GetSpawnEntity() const
    {
        return ecs::ecsEngine->GetEntityManager()->GetEntity(healthEntityId);
    }

    auto GetTankEntity()
    {
        return ecs::ecsEngine->GetEntityManager()->GetEntity(healthEntityId);
    }
    const auto GetTankEntity() const
    {
        return ecs::ecsEngine->GetEntityManager()->GetEntity(healthEntityId);
    }

public:
    GameObjectId healthEntityId;
    GameObjectId spawnEntityId;
    GameObjectId tankEntityId;
};
