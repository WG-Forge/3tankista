#pragma once

#include "utility/matrix.hpp"

#include "ecs.h"

class SpawnPositionComponent : public ecs::Component<SpawnPositionComponent>
{
public:
    SpawnPositionComponent() = default;
    explicit SpawnPositionComponent(const Vector3i& spawnPosition)
        : spawnPosition(spawnPosition)
    {
    }
    ~SpawnPositionComponent() override = default;

public:
    void SetSpawnPosition(const Vector3i& spawnPosition)
    {
        this->spawnPosition = spawnPosition;
    }
    auto&       GetSpawnPosition() { return this->spawnPosition; }
    const auto& GetSpawnPosition() const { return this->spawnPosition; }

private:
    Vector3i spawnPosition;
};
