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

e_ipVersion recognize_ip_version(const std::string &str)
{
    e_ipVersion result = IP_NA;

    // look for position of ::
    for(unsigned char i = 1; i <= MAX_IPV6_ADDRESS_STR_LEN; i++) 
    {
        switch (str[i])
        {
            case '.':
                result = IP_v4;
                return result;   
            case ':':
                result = IP_v6;
                return result; 
            case '\0': 
                return result;    
            default:
                break;
        }
    }

    return result;
}
