
#include "main.h"

int main(int argc, char* argv[])
{
          appConfig app_cfg("../config");
             Server srv(app_cfg);
             Client cli(app_cfg);

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
            srv.accept();
            srv.read();
            srv.write();
            break;
        case CLIENT:
            cli.connect_tcp_socket();
            cli.write("hello");
            cli.read();
            break;
        case NA:
        default:
            break;
    }

    return 0;
}