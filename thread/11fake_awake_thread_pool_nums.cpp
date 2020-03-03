#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <list>
using namespace std;

class A
{
public:
    // 使用condition_variable wait() notify_one()
    // 接收消息放入队列
    void recvMsg()
    {
        for(int i=0; i<10000; i++)
        {
            cout << "recvMsg(), insert a element: " << i << endl;

            std::unique_lock<std::mutex> unqlck(myMutex1); // 两个线程中的锁可能会竞争，不一定谁会拿到锁
            msgQueue.push_back(i);
            // 如果相关线程正在处理其他代码，并没有在wait()阻塞，那么这个notify_one()无效。
            // （这种情况在wait()被唤醒过后并且其中第二个参数返回true，将继续往下执行的代码）
            myCond.notify_one(); // 尝试唤醒阻塞在wait()的那个线程，（如果wait醒了就要干活，首先获取锁，然后干正事）
        }
    }
    void outMsg()
    {
        while(true)
        {
            std::unique_lock<std::mutex> unqlck(myMutex1); //// 两个线程中的锁可能会竞争，不一定谁会拿到锁

            myCond.wait(unqlck, [this]() // 第一个参数为unique_lock对象
            {
                if(!msgQueue.empty()) // 防止虚假唤醒，拿到锁之后先判断有没有数据，然后在操作数据，也许被通知的子线程不止这一个，可能其他线程拿走了中数据
                    return true;
                return false;
            });
            // 如果能够执行到这里，锁一定会被锁住的，
            // msgQueue也一定会有数据， 如果wait里边没有判断msgQueue.empty()则不一定取得到数据，，这种情况叫“虚假唤醒”，
            cmd = msgQueue.front();
            msgQueue.pop_front();
            unqlck.unlock(); // unique_lock可以提前解锁,以免被锁太长时间
            cout << "outMsg(), out msg: " << cmd << endl;

        }
    }
private:
    int cmd;
    list<int> msgQueue;
    std::mutex myMutex1;
    std::condition_variable myCond; // condition_variable是一个类
};

int main()
{
    // 一、补充知识
    //   虚假唤醒， 条件变量condition_variable的wait()和notify配合时容易出现的问题
    //     被notify的可能不止一个线程，所以在处理 被锁数据时 要先检查数据是否满足要求，否则可能出现 “虚假唤醒”
    //       有可能被通知的其中一个线程抢先处理了数据，在另一个线程得不到正确的结果，一定要在wait的第二个参数中正确设置判断条件

    // 二、std::atomic
    //    原子操作有对应的操作符，
    //      cout << atm << endl; << 操作符不是原子操作 
    //      atomic<int> atm1 = atm;  = 拷贝构造函数没有，编译不通过。 =赋值也不行
    //      atomic<int> atm1(atm.load()); // c++11有专门的赋值操作，原子读
    //      atm1.store(12); // 原子写

    // 三、线程池
    //  3.1场景设想
    //      服务器程序，客户端。 每来一个新用户创建一个新线程专为客户提供服务，如果是游戏客户肯定不行
    //          偶尔创建一个线程这种程序，会有bug，通常正常，可能崩溃，不稳定
    //  3.2线程池
    //      统一管理线程，循环利用线程
    //  3.3实现方式
    //      在程序启动时一次性创建多个线程 10 8  100-200。代码更稳定

    // 四、线程的数量
    //   线程数量极限2000左右，多了崩溃 
    //   尽量500个内，200个内最好


    A cmdObj;
    std::thread thread1(&A::recvMsg, &cmdObj);
    std::thread thread2(&A::outMsg, &cmdObj);
    thread1.join();
    thread2.join();

    return 0;
}
