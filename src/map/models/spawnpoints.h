#ifndef SPAWNPOINTS_H
#define SPAWNPOINTS_H

#include <vector>

#include "atspgtankspawnpoint.h"
#include "heavytankspawnpoint.h"
#include "lighttankspawnpoint.h"
#include "mediumtankspawnpoint.h"
#include "spgtankspawnpoint.h"

#include "nlohmann/json.hpp"

struct SpawnPoints
{
    SpawnPoints();

public:
    void SetLightTankSpawnPoints(
        const std::vector<LightTankSpawnPoint>& lightTankSpawnPoints)
    {
        this->lightTankSpawnPoints = lightTankSpawnPoints;
    }
    auto&       GetLightTankSpawnPoints() { return this->lightTankSpawnPoints; }
    const auto& GetLightTankSpawnPoints() const
    {
        return this->lightTankSpawnPoints;
    }

    void SetMediumTankSpawnPoints(
        const std::vector<MediumTankSpawnPoint>& mediumTankSpawnPoints)
    {
        this->mediumTankSpawnPoints = mediumTankSpawnPoints;
    }
    auto& GetMediumTankSpawnPoints() { return this->mediumTankSpawnPoints; }
    const auto& GetMediumTankSpawnPoints() const
    {
        return this->mediumTankSpawnPoints;
    }

    void SetHeavyTankSpawnPoints(
        const std::vector<HeavyTankSpawnPoint>& heavyTankSpawnPoints)
    {
        this->heavyTankSpawnPoints = heavyTankSpawnPoints;
    }
    auto&       GetHeavyTankSpawnPoints() { return this->heavyTankSpawnPoints; }
    const auto& GetHeavyTankSpawnPoints() const
    {
        return this->heavyTankSpawnPoints;
    }

    void SetSpgTankSpawnPoints(
        const std::vector<SpgTankSpawnPoint>& spgTankSpawnPoints)
    {
        this->spgTankSpawnPoints = spgTankSpawnPoints;
    }
    auto&       GetSpgTankSpawnPoints() { return this->spgTankSpawnPoints; }
    const auto& GetSpgTankSpawnPoints() const
    {
        return this->spgTankSpawnPoints;
    }

    void SetAtSpgTankSpawnPoints(
        const std::vector<AtSpgTankSpawnPoint>& atSpgTankSpawnPoints)
    {
        this->atSpgTankSpawnPoints = atSpgTankSpawnPoints;
    }
    auto&       GetAtSpgTankSpawnPoints() { return this->atSpgTankSpawnPoints; }
    const auto& GetAtSpgTankSpawnPoints() const
    {
        return this->atSpgTankSpawnPoints;
    }

private:
    std::vector<LightTankSpawnPoint>  lightTankSpawnPoints;
    std::vector<MediumTankSpawnPoint> mediumTankSpawnPoints;
    std::vector<HeavyTankSpawnPoint>  heavyTankSpawnPoints;
    std::vector<SpgTankSpawnPoint>    spgTankSpawnPoints;
    std::vector<AtSpgTankSpawnPoint>  atSpgTankSpawnPoints;
};

void to_json(nlohmann::json& j, const SpawnPoints& m);

void from_json(const nlohmann::json& j, SpawnPoints& m);

#endif // SPAWNPOINTS_H
