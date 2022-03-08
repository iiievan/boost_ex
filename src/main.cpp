#include <iostream>
#include <boost/asio.hpp>
#include <utils.h>

using namespace boost;

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cout << "Wrong parameters\n" << "Example usage 192.168.0.1 2001" << std::endl;
    }

    auto const address = asio::ip::make_address(argv[1]);
    auto const port = std::atoi(argv[2]);

    asio::io_service ios;
    system::error_code ec;
    asio::ip::tcp::acceptor acc(ios, asio::ip::tcp::endpoint(address, port));
    asio::ip::tcp::socket sock(ios);
    asio::streambuf buf;

    acc.accept(sock);

    asio::read_until(sock, buf, "\n", ec);

    BOOST_ERROR_PROCESSING(ec);

    std::string data = asio::buffer_cast<const char*>(buf.data());
    std::cout << data << std::endl;

    asio::write(sock, asio::buffer(data), ec);

    BOOST_ERROR_PROCESSING(ec);

    return 0;
}
