#ifndef __UTILS_H
#define __UTILS_H

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
                                                    return ec.value();\
                                                }

extern        char asciiToHex(char c);
extern e_ipVersion recognize_ip_version(const std::string &str);

#endif //__UTILS_H