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




