#pragma once

#include <vector>

#include "nlohmann/json.hpp"
#include "tanks/tank_types.h"
#include "utility/matrix.hpp"

struct SpawnPoints
{
public:
    using TanksTypeAndSpawnPos =
        std::vector<std::pair<TankType, std::vector<Vector3i>>>;

public:
    SpawnPoints()          = default;
    virtual ~SpawnPoints() = default;

public:
    void SetTanksSpawnPoints(TanksTypeAndSpawnPos& tanksSpawnPoints)
    {
        this->tanksSpawnPoints = std::move(tanksSpawnPoints);
    }
    auto&       GetTanksSpawnPoints() { return this->tanksSpawnPoints; }
    const auto& GetTanksSpawnPoints() const { return this->tanksSpawnPoints; }

private:
    TanksTypeAndSpawnPos tanksSpawnPoints;
};

void to_json(nlohmann::json& json, const SpawnPoints& spawnPoints);

void from_json(const nlohmann::json& json, SpawnPoints& spawnPoints);
