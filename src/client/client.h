#ifndef __CLIENT_H
#define __CLIENT_H

#include <iostream>
#include <boost/asio.hpp>
#include "utils.h"

namespace Client
{
    const boost::asio::ip::tcp::endpoint&  create_endpoint(const std::string& raw_ip, 
                                                           const unsigned short port_num)
    {   
        const boost::asio::ip::tcp::endpoint *ep = nullptr;
        boost::system::error_code error_code;
        boost::asio::ip::address ip_address = boost::asio::ip::address::from_string(raw_ip, error_code);

        if (error_code.value() != 0) 
        {
            std::cout << "Failed to parse the IP address. Error code = "
            << error_code.value() << ". Message: " << error_code.message();
            return *ep;
        }

        ep = new boost::asio::ip::tcp::endpoint(ip_address, port_num);

        return *ep;
    }    
} // namespace Client

#endif //__CLIENT_H