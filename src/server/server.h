#ifndef __SERVER_H
#define __SERVER_H

#include <iostream>
#include <boost/asio.hpp>
#include "utils.h"

namespace Server
{
    const boost::asio::ip::tcp::endpoint&  create_endpoint(const unsigned short port_num)
    {   
        const boost::asio::ip::tcp::endpoint *ep = nullptr;
        boost::asio::ip::address ip_address = boost::asio::ip::address_v6::any();

        ep = new boost::asio::ip::tcp::endpoint(ip_address, port_num);

        return *ep;
    }    
} // namespace Server

#endif //__SERVER_H