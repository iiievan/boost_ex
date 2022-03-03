#include <iostream>
#include <boost/asio.hpp>
//#include <boost/asio/ip/tcp.hpp>

namespace ba = boost::asio;

int main()
{
  ba::io_service service;

  ba::ip::tcp::endpoint ep(ba::ip::address::from_string("127.0.0.1"), 2001);
  ba::ip::tcp::socket 	sock(service);
  std::cout << "start connection.." << std::endl;
  sock.connect(ep);

  std::cout << "end connection" << std::endl;

  return 0;
}
