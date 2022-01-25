#ifndef PLAYER_H
#define PLAYER_H

#include "loginresponcemodel.h"

#include <memory>

#include "abstracttank.h"

class Player
{
public:
    Player();
    virtual ~Player();

protected:
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

#endif // PLAYER_H
