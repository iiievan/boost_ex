#ifndef __CLIENT_H
#define __CLIENT_H

#include <iostream>
#include <boost/asio.hpp>
#include "utils.h"

namespace Client
{
    boost::asio::ip::tcp::endpoint create_tcp_endpoint(const appConfig& cfg)
    {   
        return boost::asio::ip::tcp::endpoint(cfg.ip, cfg.port);
    }  

    boost::asio::ip::udp::endpoint create_udp_endpoint(const appConfig& cfg)
    {   
       return boost::asio::ip::udp::endpoint(cfg.ip, cfg.port);
    }    
} // namespace Client

#endif //__CLIENT_H