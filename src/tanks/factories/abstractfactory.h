#ifndef SERVER_ABSTRACTFACTORY_H
#define SERVER_ABSTRACTFACTORY_H

#include "../abstracttank.h"

class AbstractFactory
{
public:
    virtual AbstractTank *CreateTank(int vehicleId, Player *owner) const = 0;
};

#endif // SERVER_ABSTRACTFACTORY_H
