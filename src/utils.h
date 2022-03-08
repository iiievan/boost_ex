#ifndef __UTILS_H
#define __UTILS_H

#define BOOST_ERROR_PROCESSING(error_code)  if(error_code)\
                                            {\
                                                std::cout << ec.message() << std::endl;\
                                                return -1;\
                                            }

#endif //__UTILS_H