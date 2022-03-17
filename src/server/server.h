#ifndef __SERVER_H
#define __SERVER_H

#include <iostream>
#include <boost/asio.hpp>
#include "utils.h"
#include "parcer.h"

namespace Server
{
    boost::asio::ip::tcp::endpoint  create_tcp_endpoint(const appConfig& cfg)
    {   
        return boost::asio::ip::tcp::endpoint(cfg.ip, cfg.port); 
    } 

    boost::asio::ip::udp::endpoint  create_udp_endpoint(const appConfig& cfg)
    {   
        return boost::asio::ip::udp::endpoint(cfg.ip, cfg.port);
    }  

    boost::asio::ip::tcp::acceptor  create_tcp_acceptor(const appConfig& cfg)
    {   
        boost::asio::io_service ios;
        boost::asio::ip::tcp::acceptor acceptor(ios);
        boost::system::error_code ec;
        
        boost::asio::ip::tcp protocol_v4 = boost::asio::ip::tcp::v4();
        boost::asio::ip::tcp protocol_v6 = boost::asio::ip::tcp::v6();

        if(cfg.ip.is_v4())
            acceptor.open(protocol_v4, ec);
        else
        if(cfg.ip.is_v6())
            acceptor.open(protocol_v6, ec);
        else
        { std::cerr << "Wrong IP config!.\n"; }  

        BOOST_ERROR_AND_MSG_PROCESSING(ec, "Failed to open the acceptor socket! Error code =");

        return acceptor; 
    } 
} // namespace Server

#endif //__SERVER_H