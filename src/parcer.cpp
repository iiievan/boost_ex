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
    e_ipVersion ip_version;

    switch(_configMap[pair.first])
    {
        case SW_SERVER: 
            sw_type = SERVER;       
            break; 

        case SW_CLIENT: 
            sw_type = CLIENT;        
            break; 

        case IP:
            ip_version = recognize_ip_version(pair.second);

            switch (ip_version)
            {
                case IP_v4:
                    IPv4_fromString(pair.second);
                    break;
                case IP_v6:
                    IPv6_fromString(pair.second);
                    break;
                case IP_NA:
                default:
                    std::cerr << "Invalid IP number.\n"; 
                    break;
            }            
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

bool appConfig::IPv4_fromString(const std::string &str)
{
    memset(ipv4, 0, sizeof(ipv4));

    std::istringstream iss(str);
    std::vector<std::string> tokens;
    std::string token;

    for(unsigned char i = 0; std::getline(iss, token, '.'); i++)
    {
        if (!token.empty())
            tokens.push_back(token);                    
    }

    for(unsigned j = 0; j < 4; j++)
        ipv4[j] = std::stoi(tokens[j]);

    return false;
}

bool appConfig::IPv6_fromString(const std::string &str)
{
    unsigned short accumulator = 0;
    unsigned char  colon_count = 0;
    unsigned char  pos = 0; 

    memset(ipv6, 0, sizeof(ipv6));   

    // Step 1: look for position of ::, and count colons after it
    for(unsigned char i = 1; i <= MAX_IPV6_ADDRESS_STR_LEN; i++) 
    {
        if (str[i] == ':') 
        {
            if (str[i-1] == ':') 
            {
                // Double colon!
                colon_count = 7;
            } 
            else
            {
                if(!colon_count)
                    colon_count--;
            }               
                
        } 
        else 
        if (str[i] == '\0') 
        {
            break;
        }
    }

    // Step 2: convert from ascii to binary
    for(unsigned char i = 0; i <= MAX_IPV6_ADDRESS_STR_LEN && pos < 8; i++) 
    {
        if (str[i] == ':' || str[i] == '\0') 
        {
            ipv6[pos] = accumulator;
            accumulator = 0;

            if (colon_count && i && str[i-1] == ':') 
            {
                pos = colon_count;
            } 
            else 
            {
                pos++;
            }
        } 
        else 
        {
            char val = asciiToHex(str[i]);

            if (val == -1) 
            {
                // Not hex or colon: fail
                return false;
            } 
            else 
            {
                accumulator <<= 4;
                accumulator |= val;
            }
        }

        if (str[i] == '\0')
            break;
    }

    // Success
    return true;
}

void appConfig::print_IPv4() const
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

void appConfig::print_IPv6() const
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
        std::cout << ":" << std::dec << (int)port;
}

std::string appConfig::get_IPv4()
{
    std::string s;

    for(int i = 0; i < 4; ++i) 
    {
        s += std::to_string(ipv4[i]);

        if(i != 4 - 1)
            s += '.';
    }

    return s;
}