#include "tankfactories.h"

TankFactories::TankFactories()
{
    factories[TankType::MEDIUM_TANK] = std::shared_ptr<AbstractFactory>(new MediumTankFactory());
}

const std::shared_ptr<AbstractFactory>& TankFactories::operator[](TankType tankType)
{
    return factories[tankType];
}