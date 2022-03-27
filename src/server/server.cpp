#include "server.h"

Server::Server(boost::asio::io_service& ios, appConfig& cfg)
: s_Cfg_(cfg),
  ios_(ios),
  acceptor_(ios),
  tcp_socket_(std::make_shared<boost::asio::ip::tcp::socket>(ios_))
{
    std::cout << "Acceptor: init." << std::endl;

    //std::string raw_ip = "192.168.0.58";
    //boost::asio::ip::address ip = boost::asio::ip::address::from_string(raw_ip, ec_);
    //BOOST_ERROR_AND_MSG_PROCESSING(ec_, "Filed to parce IP address! Error code = ");

    //boost::asio::ip::tcp::endpoint endpoint(ip, s_Cfg_.port);
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), s_Cfg_.port);

    acceptor_.open(endpoint.protocol());
    acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
    acceptor_.bind(endpoint);
    acceptor_.listen();
}

void Server::open_socket()
{
     if(s_Cfg_.ip.is_v4())
         tcp_socket_->open(boost::asio::ip::tcp::v4(), ec_);
     else
     if(s_Cfg_.ip.is_v6())
         tcp_socket_->open(boost::asio::ip::tcp::v6(), ec_);
     else
         std::cerr << "Wrong IP config!.\n"; 
 
     BOOST_ERROR_AND_MSG_PROCESSING(ec_, "Filed to open socket! Error code = ");
}

void Server::accept()
{
    std::cout << "Acceptor: accept!" << std::endl;

    acceptor_.accept(*tcp_socket_);
}

void Server::open_acceptor()
{  
    if(s_Cfg_.ip.is_v4())
        acceptor_.open(boost::asio::ip::tcp::v4(), ec_);
    else
    if(s_Cfg_.ip.is_v6())
        acceptor_.open(boost::asio::ip::tcp::v6(), ec_);
    else
        std::cerr << "Wrong IP config!.\n"; 

    BOOST_ERROR_AND_MSG_PROCESSING(ec_, "Failed to open the acceptor socket! Error code =");
}

int Server::read()
{
    boost::asio::read_until(*tcp_socket_, receive_buffer_, "\n", ec_);

    BOOST_ERROR_PROCESSING(ec_);

    return 0;
}

int Server::write()
{
    data_ = boost::asio::buffer_cast<const char*>(receive_buffer_.data());
    
    std::cout << data_ << std::endl;

    boost::asio::write(*tcp_socket_, boost::asio::buffer(data_), ec_);

    BOOST_ERROR_PROCESSING(ec_); 

    return 0;
}
