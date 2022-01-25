#ifndef SPAWNPOINTS_H
#define SPAWNPOINTS_H

#include <vector>

#include "nlohmann/json.hpp"

#include "enumparser.h"
#include "matrix.hpp"

enum class TankType
{
    LIGHT,
    MEDIUM,
    HEAVY,
    AT_SPG,
    SPG
};

struct SpawnPoints
{
public:
    using TanksTypeAndSpawnPos =
        std::vector<std::pair<TankType, std::vector<Vector3d>>>;

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

void to_json(nlohmann::json& j, const SpawnPoints& m);

void from_json(const nlohmann::json& j, SpawnPoints& m);

#endif // SPAWNPOINTS_H
