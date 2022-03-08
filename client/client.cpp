/** на стороне клиента
использование: 
./client 192.168.0.94 2001 hello
**/

#include <iostream>
#include <boost/asio.hpp>

using namespace boost;

int main(int argc, char* argv[])
{
    if (argc != 4)
    {
        std::cout << "Wrong parameters\n" << "Example usage  ./client 192.168.0.94 hello" << std::endl;
        return -1;
    }

    auto const address = asio::ip::make_address(argv[1]);
    auto const port = std::atoi(argv[2]);
    std::string msg = argv[3];
    msg = msg + '\n';

    asio::io_service io;
    asio::ip::tcp::socket sock(io);
    system::error_code ec;

    sock.connect(asio::ip::tcp::endpoint(address, port), ec);

    if(ec)
    {
        std::cout << ec.message() << std::endl;
        return -1;
    }

    asio::write(sock, asio::buffer(msg), ec);

    if (ec)
    {
        std::cout << ec.message() << std::endl;
        return -1;
    }

    asio::streambuf receive_buffer;
    asio::read(sock,receive_buffer,asio::transfer_all(), ec);

    if(ec && ec != asio::error::eof)
    {
        std::cout<< "receive failed " << ec.message() << std::endl;
    }
    else
    {
        const char * data = asio::buffer_cast<const char *>(receive_buffer.data());
        std::cout << data << std::endl;
    }

    return 0;
}