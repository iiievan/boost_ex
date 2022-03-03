#include <iostream>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

int main()
{
  boost::asio::io_service io;

  boost::asio::deadline_timer t(io, boost::posix_time::seconds(10));

  std::cout << "timer start." << std::endl;

  t.wait();

  std::cout << "timer end." << std::endl;

  return 0;
}