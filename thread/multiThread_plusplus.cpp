#include <iostream>
#include <thread>
#include "time_in_code.h"
using namespace std;

void summ(long start, long end, long& ans)
{
    // 尽管是引用传递，但是不直接对引用操作，，因为引用使用指针实现的，是通过间接寻址对ans频繁++
    // 而temp在栈中，直接寻址，快很多
    long temp = ans; 
    for(int i=start; i<end; i++)
    {
        temp += i; // 在栈中操作
        // ans += i; // ans通过引用传入，这里间接寻址，频繁操作时间累积很大
    }
    ans = temp;
}


int main()
{
    const long s = 200000000;
    codeTime([&s] () 
    {
        long ans1=0, ans2=0;
        thread t1 = thread(summ, 0, s/2, std::ref(ans1)); // 在线程中传入引用的方法
        thread t2 = thread(summ, s/2, s, std::ref(ans2));
        t1.join(); // 等到运行完再往下执行
        t2.join();
        cout << "sum: " << ans1 + ans2 << endl;
    });

    codeTime([&s] ()
    {
        long ans=0;
        summ(0, s, std::ref(ans));
        cout << "sum: " << ans << endl;
    });

    return 0;
}
