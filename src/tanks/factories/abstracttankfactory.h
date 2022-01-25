#ifndef SERVER_ABSTRACTTANKFACTORY_H
#define SERVER_ABSTRACTTANKFACTORY_H

#include "../abstracttank.h"

class AbstractTankFactory
{
public:
    virtual AbstractTank *CreateMediumTank(int vehicleId) const = 0;
};

#endif // SERVER_ABSTRACTTANKFACTORY_H
