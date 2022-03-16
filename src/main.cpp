
#include "main.h"

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
            Server::create_tcp_endpoint(app_cfg.port, IP_v4);
            create_active_tcp_socket(IP_v4);
            break;
        case CLIENT:
            Client::create_tcp_endpoint(app_cfg.get_IPv4(), app_cfg.port);
            create_active_tcp_socket(IP_v4);
            break;
        case NA:
        default:
            break;
    }

    return 0;
}

int create_active_tcp_socket(e_ipVersion ip_version)
{
    boost::asio::io_service ios;
    boost::asio::ip::tcp::socket sock(ios);
    boost::system::error_code error_code;

     switch(ip_version)
    {
        case IP_v4:
            sock.open(boost::asio::ip::tcp::v4(), error_code);
            break;
        case IP_v6:
            sock.open(boost::asio::ip::tcp::v6(), error_code);
            break;
        case IP_NA:
        default:
            break;        
    }

    BOOST_ERROR_AND_MSG_PROCESSING(error_code, "Filed to open socket! Error code = ");

    return error_code.value();
    
}

int create_active_udp_socket(e_ipVersion ip_version)
{
    boost::asio::io_service ios;
    boost::asio::ip::udp::socket sock(ios);
    boost::system::error_code error_code;

     switch(ip_version)
    {
        case IP_v4:
            sock.open(boost::asio::ip::udp::v4(), error_code);
            break;
        case IP_v6:
            sock.open(boost::asio::ip::udp::v6(), error_code);
            break;
        case IP_NA:
        default:
            break;        
    }

    BOOST_ERROR_AND_MSG_PROCESSING(error_code, "Filed to open socket! Error code = ");

    return error_code.value();
    
}
