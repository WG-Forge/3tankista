#ifndef SPAWNPOINTS_H
#define SPAWNPOINTS_H

#include <vector>

#include "tankspawnpoint.h"

#include "nlohmann/json.hpp"

struct SpawnPoints
{
    SpawnPoints();

public:
    void SetSpawnPoints(const std::vector<TankSpawnPoint>& spawnPoints)
    {
        this->spawnPoints = spawnPoints;
    }
    auto&       GetSpawnPoints() { return this->spawnPoints; }
    const auto& GetSpawnPoint() const { return this->spawnPoints; }

private:
    std::vector<TankSpawnPoint> spawnPoints;
};

void to_json(nlohmann::json& j, const SpawnPoints& m);

void from_json(const nlohmann::json& j, SpawnPoints& m);

#endif // SPAWNPOINTS_H
