#ifndef FILTER_LIB_H
#define FILTER_LIB_H

#include <iostream> //std::cin,std::cout

int* filter(int* first, int* last, bool(*pred)(int) );

#endif