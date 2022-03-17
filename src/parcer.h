#ifndef __PARCER_H
#define __PARCER_H

#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <boost/assign.hpp>
#include <boost/asio.hpp>
#include "utils.h"

enum e_ipVersion : unsigned int
{
    IP_NA,               
    IP_v4,  
    IP_v6 
}; 

enum e_swType : unsigned int
{    
    NA = 0,
    SERVER,
    CLIENT
};

enum e_appPurpose : unsigned int
{
    APP_NA,
    APP_CHAT_SERVER,
    APP_WEB_SERVER,
    APP_EMAIL_SERVER,
    APP_CRYPTOCURRENCY
};

enum e_config : unsigned int
{
    SW_SERVER,               
    SW_CLIENT,  
    IP,                      
    PORT,                    
    CHAT_SERVER,             
    WEB_SERVER,   
    EMAIL_SERVER,
    CRYPTOCURRENCY
}; 

class appConfig
{
public:
        appConfig(const char* fname);  // parsing input config file

   int fill_config(std::pair<std::string,std::string> &pair);
  void print_IP();
  void print_Port();
  void print_IPandPort();

                e_swType sw_type     = NA;
boost::asio::ip::address ip;
          unsigned short port        =  65535;
            e_appPurpose app_purpose = APP_NA;

private:
std::map<std::string, e_config> _configMap; // for switch case while parsing
};



#endif