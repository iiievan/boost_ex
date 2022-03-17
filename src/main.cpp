
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

    boost::asio::io_service ios;
    boost::asio::ip::tcp::socket *socket = new boost::asio::ip::tcp::socket(ios);
    boost::asio::ip::tcp::endpoint *ep   = new boost::asio::ip::tcp::endpoint();    

    switch (app_cfg.sw_type)
    {
        case SERVER:
            *ep = Server::create_tcp_endpoint(app_cfg);
            *socket = create_active_tcp_socket(app_cfg); // and open it
            break;
        case CLIENT:
            *ep = Client::create_tcp_endpoint(app_cfg);
            *socket = create_active_tcp_socket(app_cfg); // and open it
            break;
        case NA:
        default:
            break;
    }

    boost::asio::ip::tcp::acceptor acc = Server::create_tcp_acceptor(app_cfg);

    return 0;
}