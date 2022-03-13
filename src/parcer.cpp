#include "parcer.h"

void parse_config_file(const char* fname, appConfig_t &pConfig)
{
    std::ifstream cFile(fname);

    if (cFile.is_open())
    {
        std::string line;

        while(std::getline(cFile, line))
        {
            line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());

            if(line[0] == '#' || line.empty())
            {  continue; }

            auto delimiterPos = line.find("=");
            std::string key   = line.substr(0, delimiterPos);
            std::string value = line.substr(delimiterPos + 1);

            std::pair <std::string,std::string> parce_pair = std::make_pair(key,value);

            fill_application_config(parce_pair, pConfig);
        }        
    }
    else
    {   std::cerr << "Couldn't open config file for reading.\n"; }

}

void fill_application_config(std::pair <std::string,std::string> &pair, appConfig_t &pConfig)
{
    static std::map<std::string, e_config> s_configMap;

    std::istringstream iss(pair.second);
    std::vector<std::string> tokens;
    std::string token;

    switch(s_configMap[pair.first])
    {
        case CONFIG_SW_SERVER: 
            pConfig.sw_type = SW_SERVER;       
            break;  
        case CONFIG_SW_CLIENT: 
            pConfig.sw_type = SW_CLIENT;        
            break; 
        case CONFIG_IP:
            //ipv4   
            if(pair.second[3] == '.') 
            {
                for(unsigned char i = 0; std::getline(iss, token, '.'); i++)
                {
                    if (!token.empty())
                        tokens.push_back(token);                    
                }
            }
            //ipv6
            if(pair.second[4] == ':')
            {
                for(unsigned char i = 0; std::getline(iss, token, ':'); i++)
                {
                    if (!token.empty())
                        tokens.push_back(token);                    
                }
            }

            if(tokens.size() == 4)
            {
                for(unsigned j = 0; j < 4; j++)
                    pConfig.ipv4[j] = std::stoi(tokens[j]);
            }
            else
            if(tokens.size() > 4)
            {
                for(unsigned j = 0; j < tokens.size(); j++)
                    pConfig.ipv6[j] = std::stoi(tokens[j]);  
            }
            else
            { std::cerr << "Invalid IP number.\n"; }

            break; 
        case CONFIG_PORT: 
            pConfig.port  =  std::stoi(pair.second);    
            break; 
        case CONFIG_CHAT_SERVER:  
            if(pair.second[0] == 'y') 
                pConfig.app_purpose = APP_CHAT_SERVER;     
            break; 
        case CONFIG_WEB_SERVER: 
            if(pair.second[0] == 'y') 
                pConfig.app_purpose = APP_CHAT_SERVER;          
            break;
        case CONFIG_EMAIL_SERVER:    
            if(pair.second[0] == 'y') 
                pConfig.app_purpose = APP_CHAT_SERVER;    
            break; 
        case CONFIG_CRYPTOCURRENCY:    
            if(pair.second[0] == 'y') 
                pConfig.app_purpose = APP_CRYPTOCURRENCY;    
            break; 
        default:
            break;     
    }
}