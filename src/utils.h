#ifndef __UTILS_H
#define __UTILS_H

class appConfig;
#include <string>
#include "parcer.h"

#define MAX_IPV6_ADDRESS_STR_LEN  (39)
#define BOOST_ERROR_PROCESSING(ec)  if(ec)\
                                    {\
                                        std::cout << ec.message() << std::endl;\
                                        return -1;\
                                    }

#define BOOST_ERROR_AND_MSG_PROCESSING(ec, msg)  if(ec)\
                                                {\
                                                    std::cout << msg << ec.value() << "Message:" <<ec.message() << std::endl;\
                                                }

extern char asciiToHex(char c);
extern  boost::asio::ip::tcp::socket create_active_tcp_socket(const appConfig& cfg);
extern  boost::asio::ip::udp::socket create_active_udp_socket(const appConfig& cfg);

#endif //__UTILS_H