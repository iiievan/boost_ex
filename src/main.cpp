#include <iostream>
#include <boost/asio.hpp>
#include "utils.h"
#include "client.h"
#include "parcer.h"

appConfig_t app_configuration;

int main(int argc, char* argv[])
{
    parse_config_file("config", app_configuration);

    if (argc != 4)
    {
        std::cout << "Wrong parameters\n" << "Example usage  ./client 192.168.0.94 2009 hello" << std::endl;
        return -1;
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
