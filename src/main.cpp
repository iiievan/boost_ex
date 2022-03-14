#include <iostream>
#include <boost/asio.hpp>
#include "utils.h"
#include "client.h"
#include "parcer.h"

int main(int argc, char* argv[])
{
    appConfig app_configuration("config");

    switch(app_configuration.sw_type)
    {
        case SERVER:
            std::cout << "Server started at ";
            app_configuration.print_IPv4();
            std::cout << "." << std::endl;
            break;
        case CLIENT:
            std::cout << "Client started at ";
            app_configuration.print_IPv4();
            std::cout << "." << std::endl;
            break;
        default:
            std::cout << "Error:Wrong config file parameters.\n"; 
            return -1;
            break;
    }  

    std::string const address(argv[1]);
    unsigned short const port = std::atoi(argv[2]);
    std::string msg = argv[3];
    msg = msg + '\n';

    boost::asio::ip::tcp::endpoint ep = Client::create_endpoint(address, port);
    boost::asio::io_service io;
    boost::asio::ip::tcp::socket sock(io);
    boost::system::error_code ec;

    sock.connect(ep, ec);

    BOOST_ERROR_PROCESSING(ec);

    boost::asio::write(sock, boost::asio::buffer(msg), ec);

    BOOST_ERROR_PROCESSING(ec);

    boost::asio::streambuf receive_buffer;
    boost::asio::read(sock,receive_buffer,boost::asio::transfer_all(), ec);

    if(ec && ec != boost::asio::error::eof)
    {
        std::cout<< "receive failed " << ec.message() << std::endl;
    }
    else
    {
        const char * data = boost::asio::buffer_cast<const char *>(receive_buffer.data());
        std::cout << data << std::endl;
    }

    return 0;
}
