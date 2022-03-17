#ifndef __CLIENT_H
#define __CLIENT_H

#include <iostream>
#include <boost/asio.hpp>
#include "utils.h"

namespace Client
{
    const boost::asio::ip::tcp::endpoint&  create_tcp_endpoint(const appConfig& cfg)
    {   
        const boost::asio::ip::tcp::endpoint *ep = nullptr;

        ep = new boost::asio::ip::tcp::endpoint(cfg.ip, cfg.port);

        return *ep;
    }  

    const boost::asio::ip::udp::endpoint&  create_udp_endpoint(const appConfig& cfg)
    {   
        const boost::asio::ip::udp::endpoint *ep = nullptr;

        ep = new boost::asio::ip::udp::endpoint(cfg.ip, cfg.port);

        return *ep;
    }    
} // namespace Client

#endif //__CLIENT_H