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
    void setData(const ServerModels::ClientDataModel& data)
    {
        this->data = data;
    }
    auto&       Data() { return this->data; }
    const auto& Data() const { return this->data; }

    void setTanks(const std::vector<Tank>& vehicles)
    {
        this->vehicles = vehicles;
    }
    auto&       tanks() { return this->vehicles; }
    const auto& tanks() const { return this->vehicles; }

private:
    ServerModels::ClientDataModel data;
    std::vector<Tank>             vehicles;
};

#endif // PLAYER_H
