/** на стороне клиента
сборка: 
g++ -pthread -lboost_system client.cpp -o client
использование: 
./client 192.168.0.94 2001 hello
**/

#include <iostream>
#include <boost/asio.hpp>

int main(int argc, char* argv[])
{
    if (argc != 4)
    {
        std::cout << "Wrong parameters\n" << "Example usage  ./client 192.168.0.94 hello" << std::endl;
        return -1;
    }

    auto const address = boost::asio::ip::make_address(argv[1]);
    auto const port = std::atoi(argv[2]);
    std::string msg = argv[3];
    msg = msg + '\n';

    boost::asio::io_service io;
    boost::asio::ip::tcp::socket sock(io);
    boost::system::error_code ec;

    sock.connect(boost::asio::ip::tcp::endpoint(address, port), ec);

    if(ec)
    {
        std::cout << ec.message() << std::endl;
        return -1;
    }

    boost::asio::write(sock, boost::asio::buffer(msg), ec);

    if (ec)
    {
        std::cout << ec.message() << std::endl;
        return -1;
    }

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