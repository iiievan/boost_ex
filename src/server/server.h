#ifndef __SERVER_H
#define __SERVER_H

#include <iostream>
#include <boost/asio.hpp>
#include "utils.h"
#include "parcer.h"

class Server
{
public:
                                    Server(appConfig& cfg);
                                    ~Server();

    boost::asio::ip::tcp::endpoint& create_tcp_endpoint();
    boost::asio::ip::udp::endpoint& create_udp_endpoint();
    boost::asio::ip::tcp::acceptor& create_acceptor();      // meaning tcp acceptor
                               void create_active_tcp_socket();
                               void create_active_udp_socket();

private:
                         appConfig &s_Cfg_;
           boost::asio::io_service ios_;
         boost::system::error_code ec_;

      boost::asio::ip::tcp::socket *tcp_socket_;
    boost::asio::ip::tcp::acceptor *acceptor_;
    boost::asio::ip::tcp::endpoint *tcp_ep_;

      boost::asio::ip::udp::socket *udp_socket_;
    boost::asio::ip::udp::endpoint *udp_ep_; 
};

#endif //__SERVER_H