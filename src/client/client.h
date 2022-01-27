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
    virtual ~Client();

public:
    bool Login(const ServerModels::LoginRequestModel& data);
    bool Logout();

private:
    void SetData(const ServerModels::ClientDataModel& data)
    {
        this->data = data;
    }
    auto&       GetData() { return this->data; }
    const auto& GetData() const { return this->data; }

    void        SetResult(const Server::Result& result) { lastResult = result; }
    auto&       GetResult() { return this->lastResult; }
    const auto& GetResult() const { return this->lastResult; }

private:
    // TODO check how many bytes use idx
    ServerModels::ClientDataModel data;
    Server::Result                lastResult;
};

#endif // CLIENT_H
