#pragma once

#include "server/models/login_request_model.h"
#include "server/models/login_responce_model.h"
#include "server/server.h"
#include <string>

class Client
{
public:
    Client()          = default;
    virtual ~Client() = default;

public:
    bool Login(const ServerModels::LoginRequestModel& data);
    bool Logout();

public:
    void SetData(ServerModels::ClientDataModel& data)
    {
        this->data = std::move(data);
    }
    auto&       GetData() { return this->data; }
    const auto& GetData() const { return this->data; }

    void        SetResult(const Server::Result& result) { lastResult = result; }
    auto&       GetResult() { return this->lastResult; }
    const auto& GetResult() const { return this->lastResult; }

private:
    ServerModels::ClientDataModel data;
    Server::Result                lastResult;
};
