#ifndef SERVER_FACTORIES_H
#define SERVER_FACTORIES_H

#include <unordered_map>
#include "../abstracttank.h"
#include "abstractfactory.h"
#include "mediumtankfactory.h"

class TankFactories
{
public:
    TankFactories();
    const std::shared_ptr<AbstractFactory>& operator[](TankType tankType);

private:
    void SetFactories(const std::unordered_map<TankType, std::shared_ptr<AbstractFactory>>& factories) { this->factories = factories; }
    auto& GetFactories() { return this->factories; }
    const auto& GetFactories() const { return this->factories; }

private:
    std::unordered_map<TankType, std::shared_ptr<AbstractFactory>> factories;
};

#endif // SERVER_FACTORIES_H
