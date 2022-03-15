#ifndef __UTILS_H
#define __UTILS_H

#include <string>

enum e_ipVersion : unsigned int
{
    IP_NA,               
    IP_v4,  
    IP_v6 
}; 

#define MAX_IPV6_ADDRESS_STR_LEN  (39)
#define BOOST_ERROR_PROCESSING(error_code)  if(error_code)\
                                            {\
                                                std::cout << ec.message() << std::endl;\
                                                return -1;\
                                            }

extern        char asciiToHex(char c);
extern e_ipVersion recognize_ip_version(const std::string &str);

#endif //__UTILS_H