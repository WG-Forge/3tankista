#ifndef CLIENT_H
#define CLIENT_H

#include <string>

#include "loginrequestmodel.h"
#include "loginresponcemodel.h"
#include "player.h"
#include "server.h"

class Client : public Player
{
public:
    Client();
    virtual ~Client();

public:
    bool Login(const ServerModels::LoginRequestModel& data);
    bool Logout();

private:
    void  setResult(const Server::Result& result) { this->lastResult = result; }
    auto& Result() { return this->lastResult; }
    const auto& Result() const { return this->lastResult; }

private:
    // TODO check how many bytes use idx
    Server::Result lastResult;
};

#endif // CLIENT_H
