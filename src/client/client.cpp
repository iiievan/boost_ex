#include"client.h"

Client::Client(boost::asio::io_service& ios, appConfig& cfg)
: s_Cfg_(cfg),
  ios_(ios),
  tcp_socket_(std::make_shared<boost::asio::ip::tcp::socket>(ios_))
{
    std::cout << "Client: init." << std::endl;
}

void Client::find_server()
{
    boost::asio::ip::tcp::resolver::query resolver_query("rpiserver", 
                                                         "2009",boost::asio::ip::tcp::resolver::query::numeric_service);  // for quick resolve

    boost::asio::ip::tcp::resolver resolver(ios_);

    boost::asio::ip::tcp::resolver::iterator it = resolver.resolve(resolver_query, ec_);

    BOOST_ERROR_AND_MSG_PROCESSING(ec_, "Filed to resolve server name! Error code = ");

    if(ec_)
        return;

    boost::asio::ip::tcp::resolver::iterator it_end;

    // print all finded endpoints of the collection
    while (it != it_end)
    {
        boost::asio::ip::tcp::endpoint endpoint = *it++;
        std::cout << endpoint << std::endl;
    }    
}

void Client::connect_socket()
{
    boost::asio::ip::tcp::endpoint endpoint(s_Cfg_.ip, s_Cfg_.port);

    tcp_socket_->connect(endpoint, ec_);

    BOOST_ERROR_AND_MSG_PROCESSING(ec_, "Filed to connect socket! Error code = ");
}

void Client::open_socket()
{
    boost::asio::ip::tcp::endpoint endpoint(s_Cfg_.ip, s_Cfg_.port);

    tcp_socket_->open(endpoint.protocol(), ec_);

    BOOST_ERROR_AND_MSG_PROCESSING(ec_, "Filed to open socket! Error code = ");
}

void Client::close_socket()
{
    ios_.post([this]() 
    {
        tcp_socket_->close();
        
        // As long as outstanding completion handlers do not
        // invoke operations on tcp_socket_, then tcp_socket_ can be 
        // destroyed.
        tcp_socket_->release();
    });
}

int Client::write(const std::string msg)
{
	std::string message = msg + '\n';
	std::printf("Sending message: %s\n", msg.c_str());

    boost::asio::write(*tcp_socket_, boost::asio::buffer(message), ec_);

    BOOST_ERROR_PROCESSING(ec_);

    return 0;
}

void Client::read()
{
    boost::asio::read(*tcp_socket_,receive_buffer_,boost::asio::transfer_all(), ec_);

    if(ec_ && ec_ != boost::asio::error::eof)
    {
        std::cout<< "Client: receive failed... " << ec_.message() << std::endl;
    }
    else
    {
        const char * data = boost::asio::buffer_cast<const char *>(receive_buffer_.data());

        std::cout <<"Server: ";
        std::cout << data << std::endl;
    }
}
