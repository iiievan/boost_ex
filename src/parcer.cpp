#include "parcer.h"

appConfig::appConfig(const char* fname)
{
    _configMap = boost::assign::map_list_of("CONFIG_SW_SERVER",     SW_SERVER)
                                           ("CONFIG_SW_CLIENT",     SW_CLIENT)
                                           ("CONFIG_IP",            IP)
                                           ("CONFIG_PORT",          PORT)
                                           ("CONFIG_CHAT_SERVER",   CHAT_SERVER)
                                           ("CONFIG_WEB_SERVER",    WEB_SERVER)
                                           ("CONFIG_EMAIL_SERVER",  EMAIL_SERVER)
                                           ("CONFIG_CRYPTOCURRENCY",CRYPTOCURRENCY);
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

            std::pair <std::string,std::string> parce_pair = std::make_pair(line.substr(0, delimiterPos),
                                                                            line.substr(delimiterPos + 1));

            fill_config(parce_pair);
        }        
    }
    else
    {   std::cerr << "Couldn't open config file for reading.\n"; }

}

void appConfig::fill_config(std::pair <std::string,std::string> &pair)
{
    std::istringstream iss(pair.second);
    std::vector<std::string> tokens;
    std::string token;

    switch(_configMap[pair.first])
    {
        case SW_SERVER: 
            sw_type = SERVER;       
            break;  
        case SW_CLIENT: 
            sw_type = CLIENT;        
            break; 
        case IP:
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
                    ipv4[j] = std::stoi(tokens[j]);
            }
            else
            if(tokens.size() > 4)
            {
                for(unsigned j = 0; j < tokens.size(); j++)
                    ipv6[j] = std::stoul(tokens[j],nullptr, 16);  
            }
            else
            { std::cerr << "Invalid IP number.\n"; }

            break; 
        case PORT: 
            port  =  std::stoi(pair.second);    
            break; 
        case CHAT_SERVER:  
            if(pair.second[0] == 'y') 
                app_purpose = APP_CHAT_SERVER;     
            break; 
        case WEB_SERVER: 
            if(pair.second[0] == 'y') 
                app_purpose = APP_CHAT_SERVER;          
            break;
        case EMAIL_SERVER:    
            if(pair.second[0] == 'y') 
                app_purpose = APP_CHAT_SERVER;    
            break; 
        case CRYPTOCURRENCY:    
            if(pair.second[0] == 'y') 
                app_purpose = APP_CRYPTOCURRENCY;    
            break; 
        default:
            break;     
    }
}

void appConfig::print_IPv4()
{
    for(unsigned i = 0; i < 4; i++)
    {
        std::cout << (int)ipv4[i];

        if(i < 3)
            std::cout << ".";
    }

    if(port != 0xffff)
        std::cout << ":" << (int)port;
}

void appConfig::print_IPv6()
{
    bool leading_zeroes = false;
    std::cout << "[";
    for(unsigned i = 0; i < 8; i++)
    {
        if(ipv6[i] == 0)
        {
            std::cout << "";
            leading_zeroes = true;
        }
        else
        {
            if(leading_zeroes)
            {
                std::cout << ":";
                leading_zeroes = false;
            }
            std::cout << std::hex << ipv6[i];
        }            

        if(i < 7 && !leading_zeroes)
            std::cout << ":";
    }
    std::cout << "]";

    if(port != 0xffff)
        std::cout << ":" << (int)port;
}