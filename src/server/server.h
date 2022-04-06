#ifndef __SERVER_H
#define __SERVER_H

#include <iostream>
#include <cstdlib>
#include <memory>
#include <utility>
#include <boost/asio.hpp>
#include "utils.h"
#include "parcer.h"

class Server
{
public:
                                    Server(boost::asio::io_service& ios, appConfig& cfg);
                                   ~Server() { close_socket(); }

                              void  accept();
                              void  open_socket();     // active socket
                              void  close_socket();    // active socket
                              void  open_acceptor();   // passive socket
 
                               int  read();    
                               int  write();
private:

                         appConfig &s_Cfg_;
         boost::system::error_code  ec_;

           boost::asio::io_service &ios_;
           	      boost::asio::ip::tcp::acceptor  acceptor_;
   std::shared_ptr<boost::asio::ip::tcp::socket>  tcp_socket_;
                          boost::asio::streambuf  receive_buffer_;
                                     std::string  data_;
};

#endif //__SERVER_H
