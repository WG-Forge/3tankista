#pragma once

#include "server/models/login_responce_model.h"
#include "tanks/abstract_tank.h"
#include <memory>

class Player
{
public:
    Player()          = default;
    virtual ~Player() = default;

public:
    void SetData(ServerModels::ClientDataModel& data)
    {
        this->data = std::move(data);
    }
    auto&       GetData() { return this->data; }
    const auto& GetData() const { return this->data; }

    void SetTanks(std::vector<std::shared_ptr<AbstractTank>>& vehicles)
    {
        this->vehicles = std::move(vehicles);
    }
    auto&       GetTanks() { return this->vehicles; }
    const auto& GetTanks() const { return this->vehicles; }

private:
    ServerModels::ClientDataModel              data;
    std::vector<std::shared_ptr<AbstractTank>> vehicles;
};

void to_json(nlohmann::json& json, const Player& player);

void from_json(const nlohmann::json& json, Player& player);
