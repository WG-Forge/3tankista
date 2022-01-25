#include <chrono>
#include <iostream>
#include <thread>

#include "client.h"
#include "map.h"
#include "server.h"
#include "singleton.h"

#include "abstracttank.h"
#include "nlohmann/json.hpp"

int main()
{
    Client client;
    auto   isSuccessfully = client.Login(
        ServerModels::LoginRequestModel{ "kto", "ty", "ya", 25, 1, false });
    if (!isSuccessfully)
    {
        std::cerr << "Some error occurred while trying to login to the "
                     "server"
                  << std::endl;
    }
    auto kek       = "{\"1\": {\n"
                     "      \"player_id\": 1,\n"
                     "      \"vehicle_type\": \"medium_tank\",\n"
                     "      \"health\": 2,\n"
                     "      \"spawn_position\": {\n"
                     "        \"x\": -7,\n"
                     "        \"y\": -3,\n"
                     "        \"z\": 10\n"
                     "      },\n"
                     "      \"position\": {\n"
                     "        \"x\": -7,\n"
                     "        \"y\": -3,\n"
                     "        \"z\": 10\n"
                     "      },\n"
                     "      \"capture_points\": 0\n"
                     "    }}"_json;
    auto kek1 = kek.get<AbstractTank*>();
    isSuccessfully = client.Logout();
    if (!isSuccessfully)
    {
        std::cerr << "Some error occurred while trying to log out of the "
                     "server"
                  << std::endl;
    }

    return 0;
}

// TODO:
// 1) парсинг данных;                        +
// 2) обработкка ошибок работы с сервером;   -
