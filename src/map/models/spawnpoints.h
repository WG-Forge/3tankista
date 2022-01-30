#ifndef SPAWNPOINTS_H
#define SPAWNPOINTS_H

#include <vector>

#include "nlohmann/json.hpp"

#include "matrix.hpp"
#include "tanktypes.h"

struct SpawnPoints
{
public:
    using TanksTypeAndSpawnPos =
        std::vector<std::pair<TankType, std::vector<Vector3i>>>;

public:
    SpawnPoints();

public:
    void SetTanksSpawnPoints(const TanksTypeAndSpawnPos& tanksSpawnPoints)
    {
        this->tanksSpawnPoints = tanksSpawnPoints;
    }
    auto&       GetTanksSpawnPoints() { return this->tanksSpawnPoints; }
    const auto& GetTanksSpawnPoints() const { return this->tanksSpawnPoints; }

private:
    TanksTypeAndSpawnPos tanksSpawnPoints;
};

void to_json(nlohmann::json& json, const SpawnPoints& spawnPoints);

void from_json(const nlohmann::json& json, SpawnPoints& spawnPoints);

#endif // SPAWNPOINTS_H
