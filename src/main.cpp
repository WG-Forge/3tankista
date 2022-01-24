#include <iostream>

#include "client.h"
#include "server.h"
#include "singleton.h"

int main()
{
    Client client;
    auto   isSuccessfully = client.Login(
        ServerModels::LoginRequestModel{ "Ty", "nykto", "YA", 25, 1, false });
    if (!isSuccessfully)
    {
        std::cerr << "Some error occurred while trying to login to the "
                     "server"
                  << std::endl;
    }
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
