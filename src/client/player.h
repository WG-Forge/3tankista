#ifndef PLAYER_H
#define PLAYER_H

#include "loginresponcemodel.h"

#include <memory>

#include "abstracttank.h"

class Player
{
public:
    Player()          = default;
    virtual ~Player() = default;

public:
    void SetData(const ServerModels::ClientDataModel& data)
    {
        this->data = data;
    }
    auto&       GetData() { return this->data; }
    const auto& GetData() const { return this->data; }

    void SetTanks(const std::vector<std::shared_ptr<AbstractTank>>& vehicles)
    {
        this->vehicles = vehicles;
    }
    auto&       GetTanks() { return this->vehicles; }
    const auto& GetTanks() const { return this->vehicles; }

private:
    ServerModels::ClientDataModel              data;
    std::vector<std::shared_ptr<AbstractTank>> vehicles;
};

void to_json(nlohmann::json& json, const Player& player);

void from_json(const nlohmann::json& json, Player& player);

#endif // PLAYER_H
