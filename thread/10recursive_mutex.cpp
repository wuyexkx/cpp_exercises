#include <iostream>
#include <thread>
#include <vector>
#include <list>
#include <mutex>
#include <windows.h>
using namespace std;

#define __WINDOWSJQ_ // 自定义的，用于区分windows系统
class A
{
public:
    A() 
    {
#ifdef __WINDOWSJQ_
        InitializeCriticalSection(&my_winsec); // 使用临界区必须初始化
#endif
    }
    void capCmd()
    {
        for(int i=0; i<1000; i++)
        {
#ifdef __WINDOWSJQ_
            EnterCriticalSection(&my_winsec); // 加锁
            cmdQueue.push_back(i);
            LeaveCriticalSection(&my_winsec); // 解锁
#else
            myMutex.lock();
            cmdQueue.push_back(i);
            myMutex.unlock();
#endif
            cout << "push command is: " << i << endl;
        }
    }
    void exeCmd()
    {
        for(int i=0; i<1000; i++)
        {   
#ifdef __WINDOWSJQ_
            EnterCriticalSection(&my_winsec);            
            if(!cmdQueue.empty())
            {
                cout << "exe command is: " << cmdQueue.front() << endl;
                cmdQueue.pop_front();
                LeaveCriticalSection(&my_winsec);
            }
            else 
            {
                LeaveCriticalSection(&my_winsec);                
                cout << "command queue is empty.\n";
            }
#else
            // std::lock_guard<std::mutex> myguard(myMutex); // 写在这里，生命周期就是for循环。 可以写在 {} 里提前析构
            myMutex.lock(); // 加锁
            if(!cmdQueue.empty())
            {
                cout << "exe command is: " << cmdQueue.front() << endl;
                cmdQueue.pop_front();
                myMutex.unlock(); // 解锁，虽然有两个解锁的代码， 逻辑上永远只会执行其中一个 与加锁对应
            }
            else 
            {
                myMutex.unlock(); // 解锁
                cout << "command queue is empty.\n";
            }
#endif
        }
    }
private:
    list<int> cmdQueue;
    std::mutex myMutex; // 创建一个互斥量
#ifdef __WINDOWSJQ_
    CRITICAL_SECTION my_winsec; // windows中的临界区（必须初始化），非常类似c++11中的mutex
#endif
};

int main()
{
// 之前的程序都是针对c++语言的编程，对于windows有专用的工具，windows临界区类似于c++11的mutex

    // 一、windows临界区
    // 二、多次进入临界区
    //     EnterCriticalSection(&my_winsec); // 加锁
    //     EnterCriticalSection(&my_winsec); // 可以多次进入临界区，但是需要对应次数Leave
    //     LeaveCriticalSection(&my_winsec);
    //     LeaveCriticalSection(&my_winsec); // 可以多次进入临界区，但是需要对应次数Leave
    //     但是c++11的mutex不能多次lock，否则异常
    // 三、自动析构技术   术语：RAII类(Resource Acquire is initialization)
    //     std::lock_guard, 出作用域自动析构
    //     类似std::lock_guard自动析构，也可以自己给临界区变量写一个类，Enter放入构造，Leave放入析构
    //       struct Critical_Section 
    //       { 
    //          C_S(CRITICAL_SECTION* win_critical)
    //          : m_winCritical(win_critical)
    //          { EnterCriticalSection(m_winCritical); } 
    //          ~C_S(){ LeaveCriticalSection(m_winCritical); }
    //        private:
    //           CRITICAL_SECTION* m_winCritical;
    //       }
    //       这种类叫做 RAII类(Resource Acquisition Is Initialization) 自动获取和释放资源，
    //          是c++等编程语言常用的管理资源、避免内存泄露的方法。容器，智能指针都是这种东西

    // 四、recursive_mutex 递归的独占互斥量，允许同一线程同一互斥量多次被lock。但是效率低一些，递归次数有限制，够用
    //     std::mutex 独占互斥量，不能多次lock

    // 五、带超时的互斥量std::timed_mutex和 std::recursive_timed_mutex
    //   std::timed_mutex 带超时功能的独占互斥量
    //      try_lock_for(), 等待一段时间，如果拿到锁或者超时没拿到 都会继续往下执行
              // std::timed_mutex my_mutex;
              // std::chrono::milliseconds dur(100);
              // if(my_mutex.try_lock_for(dur))
              // {
              //     // 在100毫秒内拿到了锁
              //     // ...
              //     my_mutex.unlock();
              // }
              // else
              // {
              //     // 没拿到锁
              //     // ...
              // }
    //      try_lock_until(); // 类似try_lock_for，参数是未来的一个时间点
              // std::timed_mutex my_mutex;
              // std::chrono::milliseconds dur(100);
              // if(my_mutex.try_lock_until(std::chrono::steady_clock::now() + dur)) // 当前时间再加一个时间段
              // {
              //     // 在100毫秒内拿到了锁
              //     // ...
              //     my_mutex.unlock();
              // }
              // else
              // {
              //     // 没拿到锁
              //     // ...
              // }
    //   std::recursive_timed_mutex 带超时功能的递归独占互斥量，允许同一线程多次获取这个互斥量
    
    A a;
    std::thread mythread1(&A::capCmd, &a);
    std::thread mythread2(&A::exeCmd, &a);
    mythread1.join();
    mythread2.join();

    return 0;
}
