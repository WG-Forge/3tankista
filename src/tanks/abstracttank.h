#ifndef SERVER_ABSTRACTTANK_H
#define SERVER_ABSTRACTTANK_H

#include "nlohmann/json.hpp"

#include "matrix.hpp"
#include "tanktypes.h"
#include <memory>

class AbstractTank
{
public:
    AbstractTank(int vehicleId, const TankType& tankType);
    virtual ~AbstractTank();

    virtual bool CanShoot(const Vector3i& point) const = 0;
    virtual bool CanMove(const Vector3i& point) const  = 0;

    void Shoot(const Vector3i& point);
    void Move(const Vector3i& point);

protected:
    void        SetVehicleId(const int& id) { this->vehicleId = id; }
    auto&       GetVehicleId() { return vehicleId; }
    const auto& GetVehicleId() const { return vehicleId; }

public:
    void        SetPlayerId(const int& id) { this->playerId = id; }
    auto&       GetPlayerId() { return playerId; }
    const auto& GetPlayerId() const { return playerId; }

protected:
    void  SetTankType(const TankType& tankType) { this->tankType = tankType; }
    auto& GetTankType() { return tankType; }
    const auto& GetTankType() const { return tankType; }

public:
    void  SetPosition(const Vector3i& position) { this->position = position; }
    auto& GetPosition() { return this->position; }
    const auto& GetPosition() const { return this->position; }

    void SetSpawnPosition(const Vector3i& position)
    {
        this->spawnPosition = position;
    }
    auto&       GetSpawnPosition() { return this->spawnPosition; }
    const auto& GetSpawnPosition() const { return this->spawnPosition; }

    void        SetHealth(const int& health) { this->health = health; }
    auto&       GetHealth() { return this->health; }
    const auto& GetHealth() const { return this->health; }

    void  SetMaxHealth(const int& maxHealth) { this->maxHealth = maxHealth; }
    auto& GetMaxHealth() { return this->maxHealth; }
    const auto& GetMaxHealth() const { return this->maxHealth; }

    void        SetSpeed(const int& speed) { this->speed = speed; }
    auto&       GetSpeed() { return this->speed; }
    const auto& GetSpeed() const { return this->speed; }

    void        SetDamage(const int& damage) { this->damage = damage; }
    auto&       GetDamage() { return this->damage; }
    const auto& GetDamage() const { return this->damage; }

    void SetDestructionPoints(const int& destructionPoints)
    {
        this->destructionPoints = destructionPoints;
    }
    auto&       GetDestructionPoints() { return this->destructionPoints; }
    const auto& GetDestructionPoints() const { return this->destructionPoints; }

    void SetCapturePoints(const int& capturePoints)
    {
        this->capturePoints = capturePoints;
    }
    auto&       GetCapturePoints() { return capturePoints; }
    const auto& GetCapturePoints() const { return capturePoints; }

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
    static AbstractTank* from_json(const json& j);

    static void to_json(json& j, AbstractTank* t);
};
} // namespace nlohmann

// void to_json(nlohmann::json& j, const AbstractTank& tank);

// void from_json(const nlohmann::json& j, AbstractTank& tank);

#endif // SERVER_ABSTRACTTANK_H
