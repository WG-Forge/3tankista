#ifndef CLIENT_H
#define CLIENT_H

#include <string>

#include "loginrequestmodel.h"
#include "loginresponcemodel.h"
#include "server.h"

class Client
{
public:
    Client();

public:
    bool Login(const ServerModels::LoginRequestModel& data);
    bool Logout();

private:
    void setData(const ServerModels::ClientDataModel& data)
    {
        this->data = data;
    }
    auto&       Data() { return this->data; }
    const auto& Data() const { return this->data; }

    void        setResult(const Server::Result& result) { lastResult = result; }
    auto&       Result() { return this->lastResult; }
    const auto& Result() const { return this->lastResult; }

private:
    // TODO check how many bytes use idx
    ServerModels::ClientDataModel data;
    Server::Result                lastResult;
};

#endif // CLIENT_H
