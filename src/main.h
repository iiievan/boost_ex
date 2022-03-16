#ifndef __MAIN_H
#define __MAIN_H

#include <iostream>
#include <boost/asio.hpp>
#include "utils.h"
#include "client.h"
#include "server.h"
#include "parcer.h"

extern int create_active_tcp_socket(e_ipVersion ip_version);
extern int create_active_udp_socket(e_ipVersion ip_version);

#endif //__MAIN_H