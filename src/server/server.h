#ifndef __SERVER_H
#define __SERVER_H

#include <iostream>
#include <boost/asio.hpp>
#include "utils.h"
#include "parcer.h"

namespace Server
{
    const boost::asio::ip::tcp::endpoint&  create_tcp_endpoint(const unsigned short port_num, e_ipVersion ip_version)
    {   
        const boost::asio::ip::tcp::endpoint *ep = nullptr;

        switch(ip_version)
        {
            case IP_v4:
                ep = new boost::asio::ip::tcp::endpoint(boost::asio::ip::address_v4(), port_num);
                break;
            case IP_v6:
                ep = new boost::asio::ip::tcp::endpoint(boost::asio::ip::address_v6(), port_num);
                break;
            case IP_NA:
            default:
                break;        
        }
        
        return *ep;
    } 

    const boost::asio::ip::udp::endpoint&  create_udp_endpoint(const unsigned short port_num, e_ipVersion ip_version)
    {   
        const boost::asio::ip::udp::endpoint *ep = nullptr;

        switch(ip_version)
        {
            case IP_v4:
                ep = new boost::asio::ip::udp::endpoint(boost::asio::ip::address_v4(), port_num);
                break;
            case IP_v6:
                ep = new boost::asio::ip::udp::endpoint(boost::asio::ip::address_v6(), port_num);
                break;
            case IP_NA:
            default:
                break;        
        }
        
        return *ep;
    }   
} // namespace Server

#endif //__SERVER_H