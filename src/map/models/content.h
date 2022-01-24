#ifndef CONTENT_H
#define CONTENT_H

#include <vector>

#include "base.h"
#include "catapult.h"
#include "obstacle.h"
#include "repair.h"

struct Content
{
    Content();

public:
    void  SetBases(const std::vector<Base>& bases) { this->bases = bases; }
    auto& GetBases() { return this->bases; }
    const auto& GetBases() const { return this->bases; }

    void SetCatapults(const std::vector<Catapult>& catapults)
    {
        this->catapults = catapults;
    }
    auto&       GetCatapults() { return this->catapults; }
    const auto& GetCatapults() const { return this->catapults; }

    void SetRepairs(const std::vector<Repair>& repairs)
    {
        this->repairs = repairs;
    }
    auto&       GetRepairs() { return this->repairs; }
    const auto& GetRepairs() const { return this->repairs; }

    void SetObstacles(const std::vector<Obstacle>& obstacles)
    {
        this->obstacles = obstacles;
    }
    auto&       GetObstacles() { return this->obstacles; }
    const auto& GetObstacles() const { return this->obstacles; }

private:
    std::vector<Base>     bases;
    std::vector<Catapult> catapults;
    std::vector<Repair>   repairs;
    std::vector<Obstacle> obstacles;
};

#endif // CONTENT_H
