#pragma once

#include <memory>

#include "server/models/login_responce_model.h"
#include "tanks/abstract_tank.h"

class Player
{
public:
    Player();
    virtual ~Player();

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
