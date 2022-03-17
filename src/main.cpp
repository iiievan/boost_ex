
#include "main.h"

int main(int argc, char* argv[])
{
    appConfig app_cfg("config");

    switch(app_cfg.sw_type)
    {
        case SERVER:
            std::cout << "Server started at ";
            app_cfg.print_IPandPort();
            std::cout << "." << std::endl;
            break;
        case CLIENT:
            std::cout << "Client started at ";
            app_cfg.print_IPandPort();
            std::cout << "." << std::endl;
            break;
        default:
            std::cerr << "Couldn't open config file for reading.\n"; 
            return -1;
            break;
    }  

    switch (app_cfg.sw_type)
    {
        case SERVER:
            Server::create_tcp_endpoint(app_cfg);
            create_active_tcp_socket(app_cfg);
            break;
        case CLIENT:
            Client::create_tcp_endpoint(app_cfg);
            create_active_tcp_socket(app_cfg);
            break;
        case NA:
        default:
            break;
    }

    return 0;
}