#ifndef __PARCER_H
#define __PARCER_H

#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <string>
#include <sstream>
#include <vector>

enum e_swType : unsigned int
{    
    SW_NA = 0,
    SW_SERVER,
    SW_CLIENT
};

enum e_appPurpose : unsigned int
{
    APP_CHAT_SERVER,
    APP_WEB_SERVER,
    APP_EMAIL_SERVER,
    APP_CRYPTOCURRENCY
};

enum e_config : unsigned int
{
    CONFIG_SW_SERVER,               
    CONFIG_SW_CLIENT,  
    CONFIG_IP,                      
    CONFIG_PORT,                    
    CONFIG_CHAT_SERVER,             
    CONFIG_WEB_SERVER,   
    CONFIG_EMAIL_SERVER,
    CONFIG_CRYPTOCURRENCY
}; 

typedef struct
{
          e_swType sw_type;
    unsigned  char ipv4[4];
    unsigned short ipv6[8];
    unsigned short port;
      e_appPurpose app_purpose;
}appConfig_t;

void parse_config_file(const char* fname, appConfig_t &pConfig);
void fill_application_config(std::pair <std::string,std::string> &pair, appConfig_t &pConfig);

#endif