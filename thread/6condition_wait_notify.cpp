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
    // // 接收消息放入队列
    // void recvMsg()
    // {
    //     for(int i=0; i<10000; i++)
    //     {
    //         std::unique_lock<std::mutex> unqlck(myMutex1); // 加锁，作用域之外自动析构,
    //         msgQueue.push_back(i);
    //         cout << "recvMsg(), insert a element: " << i << endl;
    //     }
    // }
    // // 从queue中取出一个element
    // bool outOneElmt(int& cmd)
    // {
    //     std::unique_lock<std::mutex> unqlck(myMutex1); // 加锁，作用域之外自动析构， 可以双重锁定，但是一直检查empty也影响效率
    //     if(!msgQueue.empty())
    //     {
    //         cmd = msgQueue.front();
    //         msgQueue.pop_front();
    //         return true;
    //     }
    //     return false;
    // }
    // bool outOneElmt(int& cmd)
    // {
    //     if(!msgQueue.empty()) // 双重锁定，检查
    //     {            
    //         std::unique_lock<std::mutex> unqlck(myMutex1);
    //         if(!msgQueue.empty())
    //         {
    //             cmd = msgQueue.front();
    //             msgQueue.pop_front();
    //             return true;
    //         }
    //     }
    //     return false;
    // }
    // 取出element
    // void outMsg()
    // {
    //     for(int i=0; i<10000; i++)
    //     {
    //         if(outOneElmt(cmd))
    //         {
    //             cout << "outMsg(), out msg: " << cmd << endl;
    //         }
    //         else
    //         {
    //             cout << "current queue is empty." <<endl;
    //         }
    //     }
    // }

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
        // 如果wait第二个参数为true，那么wait返回继续往下执行   (第二个参数为 callable对象)
        // 如果wait()的第二个参数是 false,那么wait()将解锁互斥量，并阻塞到这里。
        // 无第二个参数默认false效果一样，一直阻塞到其他线程调用condtion_variable这个对象的notify_one()才会继续往下执行
        while(true)
        {
            std::unique_lock<std::mutex> unqlck(myMutex1); //// 两个线程中的锁可能会竞争，不一定谁会拿到锁
            // 当其他线程调用condtion_variable这个对象的notify_one()时，wait()开始干活了，，干什么。。。
            // a) wait()不断尝试获取锁，获取不到就阻塞到这，获取到了就执行b)
            // b) 
                // b.1 如果wait第二个参数，判断参数，参数为flase那么又解锁互斥量，阻塞，再次等待被notify_one唤醒
                // b.2 如果第二个参数为true，则wait返回，程序往下执行，锁依然锁着。
                // b.3 如果没有第二个参数，则跟flase一样，释放互斥量，阻塞到这里，等待notify
            myCond.wait(unqlck, [this]() // 第一个参数为unique_lock对象
            {
                if(!msgQueue.empty())
                    return true;
                return false;
            });
            // 如果能够执行到这里，锁一定会被锁住的，
            // msgQueue也一定会有数据
            cmd = msgQueue.front();
            msgQueue.pop_front();
            unqlck.unlock(); // unique_lock可以提前解锁,以免被锁太长时间
            cout << "outMsg(), out msg: " << cmd << endl;

            // 可能这里有100ms的任务，如拿到命令，抽卡。在其他线程中唤醒时，这个线程刚好在这，那么唤醒无效
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
    // 一、条件变量，std::condition_variable、wait()、notify_one()
        // std::condition_variable是一个类，需要和互斥量配合使用
            // wait() 阻塞这里时可以被notify唤醒。会释放也会加锁互斥量，没有锁就要阻塞在这里等待被通知，通知后尝试获取锁；
            //      有锁（获取到锁就要干活了）就看第二参数为false（或无第二参数）则释放互斥量并阻塞这里等待被notify，true就继续往下执行（锁还在）
            // notify_one() 通知其他线程执行wait(), 这里要尽快释放锁，因为wait()被唤醒后第一件事就是获取锁。但是通知不一定有效，只有那边阻塞时才有效
            // notify_all()
    // 一个线程等待某个条件后才继续往下执行，另一个线程通知这个线程条件满足，触发这个线程继续执行。

    // 二、notify_all() 唤醒所有正在等待的wait(), 但是也只能通知到一个线程被唤醒，多个线程时只能平均被唤醒。notify_one()一次只唤醒一个
    
// 整个程序有问题，入命令很多，处理的很少，是否可以考虑多个线程处理命令或者入命令限流
    A cmdObj;
    std::thread thread1(&A::recvMsg, &cmdObj);
    std::thread thread2(&A::outMsg, &cmdObj);
    thread1.join();
    thread2.join();

    return 0;
}