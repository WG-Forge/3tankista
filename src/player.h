#ifndef PLAYER_H
#define PLAYER_H

#include "loginresponcemodel.h"

class Tank;

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

    void SetTanks(const std::vector<Tank>& vehicles)
    {
        this->vehicles = vehicles;
    }
    auto&       GetTanks() { return this->vehicles; }
    const auto& GetTanks() const { return this->vehicles; }

private:
    ServerModels::ClientDataModel data;
    std::vector<Tank>             vehicles;
};

#endif // PLAYER_H
