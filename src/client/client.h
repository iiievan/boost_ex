#ifndef __CLIENT_H
#define __CLIENT_H

#include <iostream>
#include <boost/asio.hpp>
#include "utils.h"

class Client
{
public:
                                    Client(boost::asio::io_service& ios, appConfig& cfg);

                               void connect_socket();
                               void open_socket();

                                int write(const std::string msg);
                               void read();

private:
                                     appConfig &s_Cfg_;
                     boost::system::error_code  ec_;

                       boost::asio::io_service &ios_;
 std::shared_ptr<boost::asio::ip::tcp::socket>  tcp_socket_;
                        boost::asio::streambuf  receive_buffer_;
                                   std::string  data_;
};

#endif //__CLIENT_H