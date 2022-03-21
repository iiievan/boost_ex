#ifndef __CLIENT_H
#define __CLIENT_H

#include <iostream>
#include <boost/asio.hpp>
#include "utils.h"

class Client
{
public:
                                    Client(appConfig& cfg);
                                    ~Client();

    boost::asio::ip::tcp::endpoint& create_tcp_endpoint();
    boost::asio::ip::udp::endpoint& create_udp_endpoint();
                               void open_active_tcp_socket();
                               void open_active_udp_socket();

                                int connect_tcp_socket();
                                int write(const std::string msg);
                               void read();


private:
                         appConfig &s_Cfg_;
           boost::asio::io_service ios_;
         boost::system::error_code ec_;

      boost::asio::ip::tcp::socket *tcp_socket_;
    boost::asio::ip::tcp::endpoint *tcp_ep_;

      boost::asio::ip::udp::socket *udp_socket_;
    boost::asio::ip::udp::endpoint *udp_ep_; 

            boost::asio::streambuf receive_buffer_;
};

#endif //__CLIENT_H