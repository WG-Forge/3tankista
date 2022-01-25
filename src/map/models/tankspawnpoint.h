#ifndef TANKSPAWNPOINT_H
#define TANKSPAWNPOINT_H

#include "matrix.hpp"

#include "nlohmann/json.hpp"

enum class TankType
{
    Light,
    Medium,
    Heavy,
    AtSpg,
    Spg
};

struct TankSpawnPoint
{
public:
    TankSpawnPoint();
    virtual ~TankSpawnPoint();

public:
    void        SetTankType(const TankType& type) { this->type = type; }
    auto&       GetTankType() { return this->type; }
    const auto& GetTankType() const { return this->type; }

    void SetSpawnPoint(const Vector3d& spawnPoint)
    {
        this->spawnPoint = spawnPoint;
    }
    auto&       GetSpawnPoint() { return this->spawnPoint; }
    const auto& GetSpawnPoint() const { return this->spawnPoint; }

private:
    TankType type;
    Vector3d spawnPoint;
};

void to_json(nlohmann::json& j, const TankSpawnPoint& m);

void from_json(const nlohmann::json& j, TankSpawnPoint& m);

#endif // TANKSPAWNPOINT_H
