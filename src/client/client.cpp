#include"client.h"

Client::Client(boost::asio::io_service& ios, appConfig& cfg)
: s_Cfg_(cfg),
  ios_(ios),
  tcp_socket_(std::make_shared<boost::asio::ip::tcp::socket>(ios_)),
{
    std::cout << "Client: init." << std::endl;
}

void Client::find_server()
{
    int i = 1;
    std::string host = s_Cfg_.server_name;
    std::string port = std::to_string(s_Cfg_.port);

    boost::asio::ip::tcp::resolver::query resolver_query(host, 
                                                         port ,
                                                         boost::asio::ip::tcp::resolver::query::numeric_service);  // for quick resolve

    boost::asio::ip::tcp::resolver resolver(ios_);

    resolve_iter_ = resolver.resolve(resolver_query, ec_);

    BOOST_ERROR_AND_MSG_PROCESSING(ec_, "Filed to resolve server name! Error code = ");

    if(ec_)
        return;

    boost::asio::ip::tcp::resolver::iterator it_end;

    // print all finded endpoints of the collection
    while (resolve_iter_ != it_end)
    {
        boost::asio::ip::tcp::endpoint endpoint = *resolve_iter_++;
        std::cout << "Found endpoints:" << std::endl;
        std::cout << "ep " << i++ << ":" << endpoint << std::endl;
    }    
}

void Client::connect_socket()
{
    std::string host = s_Cfg_.server_name;
    std::string port = std::to_string(s_Cfg_.port);

    boost::asio::ip::tcp::resolver::query resolver_query(host, 
                                                         port ,
                                                         boost::asio::ip::tcp::resolver::query::numeric_service);  // for quick resolve

    boost::asio::ip::tcp::resolver resolver(ios_);

    try
    {
        resolve_iter_ = resolver.resolve(resolver_query);

        boost::asio::connect (tcp_socket_,resolve_iter_);
    }
    catch(boost::system::system_error &e)
    {
        BOOST_ERROR_AND_MSG_PROCESSING(e, "Error occured! Error code = ");
    }
    
    /**
    boost::asio::ip::tcp::endpoint endpoint(s_Cfg_.ip, s_Cfg_.port);
    tcp_socket_->connect(endpoint, ec_);
    BOOST_ERROR_AND_MSG_PROCESSING(ec_, "Filed to connect socket! Error code = ");
    **/
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
