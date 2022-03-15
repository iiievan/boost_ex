#include <iostream>
#include <boost/asio.hpp>
#include "utils.h"
#include "client.h"
#include "server.h"
#include "parcer.h"

int main(int argc, char* argv[])
{
    appConfig app_cfg("config");

    switch(app_cfg.sw_type)
    {
        case SERVER:
            std::cout << "Server started at ";
            app_cfg.print_IPv6();
            std::cout << "." << std::endl;
            break;
        case CLIENT:
            std::cout << "Client started at ";
            app_cfg.print_IPv4();
            std::cout << "." << std::endl;
            break;
        default:
            std::cout << "Error:Wrong config file parameters.\n"; 
            return -1;
            break;
    }  

    switch (app_cfg.sw_type)
    {
        case SERVER:
            Server::create_endpoint(app_cfg.port);
            break;
        case CLIENT:
            Client::create_endpoint(app_cfg.get_IPv4(), app_cfg.port );
            break;
        case NA:
        default:
            break;
    }

    return 0;
}
