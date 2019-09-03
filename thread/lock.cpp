#include <iostream>
#include <vector>
#include <thread>
#include "time_in_code.h"
using namespace std;
std::mutex mtx; // 获取锁
void summ(int& s) // 引用
{
    for(int i=0; i<100000000; i++)
    {
        mtx.lock();
        s++;
        mtx.unlock();
    }
}

int main()
{
    codeTime([]()
    {   
        vector<thread> v;
        int s = 0;
        for(int i=0; i<4; i++)
            v.emplace_back(summ, std::ref(s)); // 多个线程都会修改 s 的值
        for(int i=0; i< 4; i++)
        {
            v[i].join();
        }
        cout << s << endl;
    });

    return 0;
}