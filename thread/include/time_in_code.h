#ifndef __TIME_IN_CODE
#define __TIME_IN_CODE

#include <iostream>
#include <chrono> 
#include "sys/time.h"

template<class T>
void codeTime(T&& X)  // universal reference
{
#if defined (__linux__) // __linux__
    struct timeval start, end;
    gettimeofday(&start, NULL);  
    X();   // callable object
    gettimeofday(&end, NULL);  
    double diff = (double)(end.tv_usec-start.tv_usec)/1000000;
    std::cout << "Takes: " << diff << "s" << std::endl;
#elif defined(_WIN32) // _WIN32
    using namespace std::chrono;
    auto start = system_clock::now();
    X();   // callable object
    duration<double> diff = system_clock::now() - start;
    std::cout << "Takes: " << diff.count() << "s" << std::endl;
#endif
}


#endif
