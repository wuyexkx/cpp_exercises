#include <iostream>
#include <vector>
#include <thread>
using namespace std;


void print(const int i)
{
    cout << i << endl;
}


int main()
{
    vector<thread> v1;
    for(int i=1; i<11; i++) // 创建多个线程, 入口print
    {
        v1.push_back(thread(print, i));
    }   
    for(auto it=v1.begin(); it!=v1.end(); it++) // 阻塞主线程
    {
        it->join();
    }
    return 0;
}
