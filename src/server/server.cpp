#include "server.h"

Server::Server(appConfig& cfg)
:s_Cfg_(cfg)
{
      tcp_socket_ = nullptr;
        acceptor_ = nullptr; 
      udp_socket_ = nullptr;
          tcp_ep_ = nullptr; 
          udp_ep_ = nullptr;
}

Server::~Server()
{

}

boost::asio::ip::tcp::endpoint& Server::create_tcp_endpoint()
{
    if(tcp_ep_ == nullptr)
        tcp_ep_ = new boost::asio::ip::tcp::endpoint(s_Cfg_.ip, s_Cfg_.port); 

    return *tcp_ep_;
}

boost::asio::ip::udp::endpoint& Server::create_udp_endpoint()
{
    if(udp_ep_ == nullptr)
        udp_ep_ = new boost::asio::ip::udp::endpoint(s_Cfg_.ip, s_Cfg_.port); 

    return *udp_ep_;
}

boost::asio::ip::tcp::acceptor& Server::create_acceptor()
{
    if(acceptor_ == nullptr)
        acceptor_ = new boost::asio::ip::tcp::acceptor(ios_);

    if(s_Cfg_.ip.is_v4())
        acceptor_->open(boost::asio::ip::tcp::v4(), ec_);
    else
    if(s_Cfg_.ip.is_v6())
        acceptor_->open(boost::asio::ip::tcp::v6(), ec_);
    else
        std::cerr << "Wrong IP config!.\n";

    BOOST_ERROR_AND_MSG_PROCESSING(ec_, "Failed to open the acceptor socket! Error code =");

    return *acceptor_; 
}

void Server::create_active_tcp_socket()
{
    if(tcp_socket_ == nullptr)
        tcp_socket_ = new boost::asio::ip::tcp::socket(ios_);

    if(s_Cfg_.ip.is_v4())
        tcp_socket_->open(boost::asio::ip::tcp::v4(), ec_);
    else
    if(s_Cfg_.ip.is_v6())
         tcp_socket_->open(boost::asio::ip::tcp::v6(), ec_);
    else
        std::cerr << "Wrong IP config!.\n"; 

    BOOST_ERROR_AND_MSG_PROCESSING(ec_, "Filed to open socket! Error code = ");

}

void Server::create_active_udp_socket()
{
    if(udp_socket_ == nullptr)
        udp_socket_ = new boost::asio::ip::udp::socket(ios_);

    if(s_Cfg_.ip.is_v4())
        udp_socket_->open(boost::asio::ip::udp::v4(), ec_);
    else
    if(s_Cfg_.ip.is_v6())
         udp_socket_->open(boost::asio::ip::udp::v6(), ec_);
    else
        std::cerr << "Wrong IP config!.\n"; 

    BOOST_ERROR_AND_MSG_PROCESSING(ec_, "Filed to open socket! Error code = ");
}