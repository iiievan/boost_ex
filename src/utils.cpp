 #include"utils.h"

char asciiToHex(char c)
{
    c |= 0x20;

    if (c >= '0' && c <= '9') 
    {
        return c - '0';
    } 
    else 
    if (c >= 'a' && c <= 'f') 
    {
        return (c - 'a') + 10;
    } 
    else 
    {
        return -1;
    }
}

std::string get_config_path(const std::string& cfg_filename)
{
	std::string execution_path = boost::dll::program_location().string();
	std::string       progname = boost::dll::program_location().filename().string();
	std::string    config_path = (execution_path - progname);

	config_path = config_path - "bin/";
	config_path = config_path + cfg_filename;

	return config_path;
}

std::string operator-(std::string source, const std::string& target)
{
    for (size_t pos, size{ target.size() }; (pos = source.find(target)) != std::string::npos; )
    {
        source.erase(source.cbegin() + pos,
        		     source.cbegin() + (pos + size));
    }

    return source;
}

extern std::string get_local_ip()
{
    std::string result = "127.0.0.1";

    std::shared_ptr<boost::asio::ip::udp::socket>  socket;

    std::string endpoint_ip_str = "192.168.0.1";
    boost::asio::io_service io_service;

    // dotted decimal IP conversion to host byte order
    auto endpoint_ip    = inet_network(endpoint_ip_str.c_str());
    auto endpoint_port  = 8000;
    auto host_port      = 8001; 

    try
    {  
        const boost::asio::ip::udp::endpoint endpoint(boost::asio::ip::address_v4(endpoint_ip), endpoint_port);
        socket = std::make_shared<boost::asio::ip::udp::socket>(io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), host_port));
        socket->connect(endpoint);

        result = socket->local_endpoint().address().to_string();
        //std::cout << result << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    // close socket
    io_service.post([&]() 
    {
        socket->close();        
        socket->release();
    });

    return result;
}




