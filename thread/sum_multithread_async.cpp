#include <iostream>
#include <thread>
#include <future>
#include <vector>
#include "time_in_code.h"
using namespace std;

long summ(long start, long end)
{
    long s = 0;
    for(long i=start; i<end; i++)
    {
        s += i;
    }
    return s;
}

const long S = 400000000;
int main()
{
    // 多线程求和
    codeTime([]()
    {
        const long K = 4; // 4 线程
        vector<future<long>> vf;
        vf.reserve(K); // 给vector预留一定空间
        for(int i=0; i<K; i++) // 切分任务
        {   // async返回future类型的值
            vf.push_back(async(summ, i == 0 ? 0 : (S / K) * i, (S / K) * (i + 1)));
        }
        long ans = 0;
        for(int i=0; i<K; i++)
        {
            ans += vf[i].get(); // 阻塞式， 得到并排结果， 等到所有线程计算结束 才获取值
        }
        cout << ans << endl;
    });

    // 单线程求和
    codeTime([] ( )
    {
        cout << summ(0, S) << endl;
    });

    //output:
    // 1914453504
    // Takes: 0.264936s
    // 1914453504
    // Takes: 1.01301s

    return 0;
}