/** на стороне сервера - это Raspberry pi
сборка: 
g++ -pthread -lboost_system server.cpp -o server
использование: 
./server 192.168.0.94 2001
**/

#include <iostream>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

// using namespace boost::asio
// using tcp::ip

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cout << "Wrong parameters\n" << "Example usage 192.168.0.1 2001" << std::endl;
    }

    auto const address = boost::asio::ip::make_address(argv[1]);
    auto const port = std::atoi(argv[2]);

    boost::asio::io_service io;
    boost::system::error_code ec;
    boost::asio::ip::tcp::acceptor acceptor_(io, boost::asio::ip::tcp::endpoint(address, port));
    boost::asio::ip::tcp::socket socket_(io);

    acceptor_.accept(socket_);

    boost::asio::streambuf buf;
    boost::asio::read_until(socket_, buf, "\n", ec);

    if(ec)
    {
        std::cout << ec.message() << std::endl;
        return -1;
    }

    std::string data = boost::asio::buffer_cast<const char*>(buf.data());
    std::cout << data << std::endl;

    boost::asio::write(socket_, boost::asio::buffer(data), ec);

    if (ec)
    {
        std::cout << ec.message() << std::endl;
        return -1;
    }

    return 0;
}