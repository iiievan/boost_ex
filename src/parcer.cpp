#include "parcer.h"


appConfig::appConfig(const char* fname)
{
    _configMap = boost::assign::map_list_of("CONFIG_SW_SERVER",     SW_SERVER)
                                           ("CONFIG_SW_CLIENT",     SW_CLIENT)
                                           ("CONFIG_SERVER_NAME",   SERVER_NAME)
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

int appConfig::fill_config(std::pair <std::string,std::string> &pair)
{
    boost::system::error_code ec;

    switch(_configMap[pair.first])
    {
        case SW_SERVER: 
            sw_type = SERVER;       
            break; 

        case SW_CLIENT: 
            sw_type = CLIENT;        
            break; 

        case SERVER_NAME: 
            server_name = pair.second;        
            break; 

        case IP:
            ip = boost::asio::ip::address::from_string(pair.second);

            if (ec.value() != 0) 
            {
                std::cout << "Failed to parse the IP address. Error code = "
                << ec.value() << ". Message: " << ec.message();
                return ec.value();
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

    return 0;
}

void appConfig::print_IP()
{
    if(ip.is_v4())
        std::cout << ip.to_string();
    if(ip.is_v6())
        std::cout << "[" << ip.to_string() << "]";
}

void appConfig::print_IPandPort()
{
    if(ip.is_v4())
        std::cout << ip.to_string() << ":" << std::dec << port;
    if(ip.is_v6())
        std::cout << "[" << ip.to_string() << "]:" << std::dec << port;
}

void appConfig::print_Port()
{
    std::cout << ":" << std::dec << port;
}
