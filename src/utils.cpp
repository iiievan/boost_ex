#include"utils.h"

char asciiToHex(char c)
{
    c |= 0x20;

    if (c >= '0' && c <= '9') 
    {
        return c - '0';
    } 
    else 
    if (c >= 'a' && c <= 'f') 
    {
        return (c - 'a') + 10;
    } 
    else 
    {
        return -1;
    }
}


int create_active_tcp_socket(const appConfig& cfg)
{
    boost::asio::io_service ios;
    boost::asio::ip::tcp::socket sock(ios);
    boost::system::error_code ec;

    if(cfg.ip.is_v4())
        sock.open(boost::asio::ip::tcp::v4(), ec);
    else
    if(cfg.ip.is_v6())
        sock.open(boost::asio::ip::tcp::v6(), ec);
    else
    { std::cerr << "Wrong IP config!.\n"; }

    BOOST_ERROR_AND_MSG_PROCESSING(ec, "Filed to open socket! Error code = ");

    return ec.value();
    
}

int create_active_udp_socket(const appConfig& cfg)
{
    boost::asio::io_service ios;
    boost::asio::ip::udp::socket sock(ios);
    boost::system::error_code ec;

    if(cfg.ip.is_v4())
        sock.open(boost::asio::ip::udp::v4(), ec);
    else
    if(cfg.ip.is_v6())
        sock.open(boost::asio::ip::udp::v6(), ec);
    else
    { std::cerr << "Wrong IP config!.\n"; }

    BOOST_ERROR_AND_MSG_PROCESSING(ec, "Filed to open socket! Error code = ");

    return ec.value();
    
}

