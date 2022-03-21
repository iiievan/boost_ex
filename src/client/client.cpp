#include"client.h"

Client::Client(appConfig& cfg)
:s_Cfg_(cfg)
{
      tcp_socket_ = nullptr;
      udp_socket_ = nullptr;
          tcp_ep_ = nullptr; 
          udp_ep_ = nullptr;
}

Client::~Client()
{

}

boost::asio::ip::tcp::endpoint& Client::create_tcp_endpoint()
{
    if(tcp_ep_ == nullptr)
        tcp_ep_ = new boost::asio::ip::tcp::endpoint(s_Cfg_.ip, s_Cfg_.port); 

    return *tcp_ep_;
}

boost::asio::ip::udp::endpoint& Client::create_udp_endpoint()
{
    if(udp_ep_ == nullptr)
        udp_ep_ = new boost::asio::ip::udp::endpoint(s_Cfg_.ip, s_Cfg_.port); 

    return *udp_ep_;
}

void Client::open_active_tcp_socket()
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

void Client::open_active_udp_socket()
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

int Client::connect_tcp_socket()
{
    if(tcp_socket_ == nullptr)
        tcp_socket_ = new boost::asio::ip::tcp::socket(ios_);

    create_tcp_endpoint();

    tcp_socket_->connect(*tcp_ep_,ec_);

    BOOST_ERROR_PROCESSING(ec_);

    return 0;
}

int Client::write(const std::string msg)
{
    boost::asio::write(*tcp_socket_, boost::asio::buffer(msg), ec_);

    BOOST_ERROR_PROCESSING(ec_);

    return 0;
}

void Client::read()
{
    boost::asio::read(*tcp_socket_,receive_buffer_,boost::asio::transfer_all(), ec_);

    if(ec_ && ec_ != boost::asio::error::eof)
    {
        std::cout<< "receive failed " << ec_.message() << std::endl;
    }
    else
    {
        const char * data = boost::asio::buffer_cast<const char *>(receive_buffer_.data());
        std::cout << data << std::endl;
    }
}
