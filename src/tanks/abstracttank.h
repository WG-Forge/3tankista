#ifndef SERVER_ABSTRACTTANK_H
#define SERVER_ABSTRACTTANK_H

#include <memory>

// TODO: Include next
class Player;
class Vector3d;

class AbstractTank
{
public:
    enum class TankType {
        MEDIUM_TANK
    };

    AbstractTank(int vehicleId, Player *owner, const TankType& tankType);
    ~AbstractTank();

    virtual bool CanHit(const Vector3d& point) const = 0;

protected:
    void        SetVehicleId(const int& id) { this->vehicleId = id; }
    auto&       GetVehicleId() { return vehicleId; }
    const auto& GetVehicleId() const { return vehicleId; }

    void        SetPPlayer(const std::shared_ptr<Player>& player) { this->player = player; }
    auto        GetPPlayer() { return this->player; }
    const auto& GetPPlayer() const {return this->player; }

    void        SetTankType(const TankType& tankType) { this->tankType = tankType; }
    auto&       GetTankType() { return tankType; }
    const auto& GetTankType() const { return tankType; }

public:
    void        SetPosition(const Vector3d& position) { this->position = position; }
    auto&       GetPosition() { return this->position; }
    const auto& GetPosition() const { return this->position; }

    void        SetSpawnPosition(const Vector3d& position) { this->spawnPosition = position; }
    auto&       GetSpawnPosition() { return this->spawnPosition; }
    const auto& GetSpawnPosition() const { return this->spawnPosition; }

    void        SetHealth(const int& health) { this->health = health; }
    auto&       GetHealth() { return this->health; }
    const auto& GetHealth() const { return this->health; }

    void        SetSpeed(const int& speed) { this->speed = speed; }
    auto&       GetSpeed() { return this->speed; }
    const auto& GetSpeed() const {return this->speed; }

    void        SetDamage(const int& damage) { this->damage = damage; }
    auto&       GetDamage() { return this->damage; }
    const auto& GetDamage() const { return this->damage; }

    void        SetDestructionPoints(const int& destructionPoints) { this->destructionPoints = destructionPoints; }
    auto&       GetDestructionPoints() { return this->destructionPoints; }
    const auto& GetDestructionPoints() const {return this->destructionPoints; }

    void        SetCapturePoints(const int& capturePoints) { this->capturePoints = capturePoints; }
    auto&       GetCapturePoints() { return capturePoints; }
    const auto& GetCapturePoints() const { return capturePoints; }

private:
    int                      vehicleId;
    std::shared_ptr<Player>  player;
    TankType                 tankType;
    Vector3d                 position;
    Vector3d                 spawnPosition;
    int                      health;
    int                      speed;
    int                      damage;
    int                      destructionPoints;
    int                      capturePoints;
};

#endif // SERVER_ABSTRACTTANK_H
