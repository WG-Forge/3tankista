#pragma once

#include "nlohmann/json.hpp"
#include "tank_types.h"
#include "utility/matrix.hpp"
#include <memory>

class AbstractTank
{
public:
    AbstractTank(int vehicleId, const TankType& tankType);
    virtual ~AbstractTank() = default;

    virtual bool CanShoot(const Vector3i& point) const = 0;
    virtual bool CanMove(const Vector3i& point) const  = 0;

    virtual void Shoot(const Vector3i& point);
    virtual void Move(const Vector3i& point);

    bool operator<(const AbstractTank& tank);

public:
    void SetVehicleId(const int& id) { this->vehicleId = id; }
    auto GetVehicleId() const { return vehicleId; }

    void SetPlayerId(const int& id) { this->playerId = id; }
    auto GetPlayerId() const { return playerId; }

protected:
    void SetTankType(const TankType& tankType) { this->tankType = tankType; }
    auto GetTankType() const { return tankType; }

public:
    void SetPosition(Vector3i& position)
    {
        this->position = std::move(position);
    }
    auto&       GetPosition() { return this->position; }
    const auto& GetPosition() const { return this->position; }

    void SetSpawnPosition(Vector3i& position)
    {
        this->spawnPosition = std::move(position);
    }
    auto&       GetSpawnPosition() { return this->spawnPosition; }
    const auto& GetSpawnPosition() const { return this->spawnPosition; }

    void SetHealth(const int& health) { this->health = health; }
    auto GetHealth() const { return this->health; }

    void SetMaxHealth(const int& maxHealth) { this->maxHealth = maxHealth; }
    auto GetMaxHealth() const { return this->maxHealth; }

    void SetSpeed(const int& speed) { this->speed = speed; }
    auto GetSpeed() const { return this->speed; }

    void SetDamage(const int& damage) { this->damage = damage; }
    auto GetDamage() const { return this->damage; }

    void SetDestructionPoints(const int& destructionPoints)
    {
        this->destructionPoints = destructionPoints;
    }
    auto GetDestructionPoints() const { return this->destructionPoints; }

    void SetCapturePoints(const int& capturePoints)
    {
        this->capturePoints = capturePoints;
    }
    auto GetCapturePoints() const { return capturePoints; }

private:
    int      vehicleId;
    int      playerId;
    TankType tankType;
    Vector3i position;
    Vector3i spawnPosition;
    int      health;
    int      maxHealth;
    int      speed;
    int      damage;
    int      destructionPoints;
    int      capturePoints;
};

namespace nlohmann
{
template <>
struct adl_serializer<AbstractTank*>
{
    static void to_json(json& json, AbstractTank* tank);

    static AbstractTank* from_json(const json& json);
};
} // namespace nlohmann
