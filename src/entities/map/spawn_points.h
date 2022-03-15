#pragma once

#include "components/spawn_position_component.h"
#include "components/tank_type_component.h"
#include "game/game_object.h"
#include <memory>

class SpawnPoints : public GameObject<SpawnPoints>
{
public:
    SpawnPoints(const ecs::EntityId& entityId, ecs::ComponentManager* componentManager);
    ~SpawnPoints() override = default;

    void SetTankTypeSpawnComponents(
        std::vector<std::pair<TankTypeComponent*, std::vector<SpawnPositionComponent*>>> tankTypeSpawnComponents)
    {
        this->tankTypeSpawnComponents = std::move(tankTypeSpawnComponents);
    }
    auto&       GetTankTypeSpawnComponents() { return this->tankTypeSpawnComponents; }
    const auto& GetTankTypeSpawnComponents() const { return this->tankTypeSpawnComponents; }

    void SetModel(const SpawnPointsModel& model);

private:
    std::vector<std::pair<TankTypeComponent*, std::vector<SpawnPositionComponent*>>> tankTypeSpawnComponents;
};
