
#include "main.h"

int main(int argc, char* argv[])
{
          appConfig app_cfg("config");
             Server srv(app_cfg);

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

    boost::asio::ip::tcp::endpoint *ep   = new boost::asio::ip::tcp::endpoint();    

    switch (app_cfg.sw_type)
    {
        case SERVER:
            *ep = srv.create_tcp_endpoint();
            srv.create_active_tcp_socket(); // and open it
            break;
        case CLIENT:
            *ep = Client::create_tcp_endpoint(app_cfg);
            //*socket = create_active_tcp_socket(app_cfg); // and open it
            break;
        case NA:
        default:
            break;
    }

    return 0;
}