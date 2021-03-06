
#include "main.h"

int main(int argc, char* argv[])
{
	std::string config_path = get_config_path("config");
    boost::asio::io_service server_ios;
    boost::asio::io_service client_ios;
    
      appConfig app_cfg(config_path.c_str());
         Server srv(server_ios, app_cfg);
         Client cli(client_ios, app_cfg);

    switch(app_cfg.sw_type)
    {
        case SERVER:
            std::cout << "Server started at ";
            app_cfg.print_IPandPort();
            std::cout << "." << std::endl;
            break;
        case CLIENT:
            std::cout << "Client started at ";
            app_cfg.print_IPandPort();
            std::cout << "." << std::endl;
            break;
        default:
            std::cerr << "Couldn't open config file for reading.\n"; 
            return -1;
            break;
    }     

    switch (app_cfg.sw_type)
    {
        case SERVER:
            srv.accept();
            srv.read();
            srv.write();
            break;
        case CLIENT:
            cli.connect_socket();
            cli.write("hello");
            cli.read();
            break;
        case NA:
        default:
            break;
    }

    return 0;
}
