#include <iostream>
#include <chrono> 
#include "sys/time.h"
using namespace std;

template<class T>
void measureTime(T&& func)  // universal reference
{
#if defined (__linux__) // __linux__
    struct timeval start, end;
    gettimeofday(&start, NULL);  
    func();   // callable object
    gettimeofday(&end, NULL);  
    double diff = (double)(end.tv_usec-start.tv_usec)/1000000;
    std::cout << "Takes: " << diff << "s" << std::endl;
#elif defined(_WIN32) // _WIN32
    using namespace std::chrono;
    auto start = system_clock::now();
    func();   // callable object
    duration<double> diff = system_clock::now() - start;
    std::cout << "Takes: " << diff.count() << "s" << std::endl;
#endif
}

void f()
{
    for(long long i=1; i<200000000; i++);
}

int main()
{

    measureTime([] () // 第一种使用方法
    {
        for(long long i=1; i<200000000; i++);
    });

    measureTime(f);  // 第二种使用方法

    return 0;
}