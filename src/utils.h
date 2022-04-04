#ifndef __UTILS_H
#define __UTILS_H

class appConfig;
#include <string>
#include "parcer.h"
#include <boost/dll.hpp>

#ifdef WINDOWS
    #include <direct.h>
    #define GetCurrentDir _getcwd
#else
    #include <unistd.h>
    #define GetCurrentDir getcwd
 #endif

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
extern std::string get_config_path(const std::string& cfg_filename);
extern std::string operator-(std::string source, const std::string& target);

#endif //__UTILS_H
