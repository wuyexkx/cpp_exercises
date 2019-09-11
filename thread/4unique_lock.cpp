#include <iostream>
#include <thread>
#include <vector>
#include <list>
#include <mutex>
using namespace std;

// 数据共享问题
// (1)只读不写数据, 多线程没有问题. 不需要特色处理
// (2)有读有写数据, 如果没有经过特殊处理,多个线程读写同一个数据一定 程序崩溃
//      最简单的处理办法, 读的时候不能写,写的时候不能读, 不能同时读,也不能同时写
// 案例
//      不同售票窗口 都在对同一座位操作
// 共享数据保护案例
//  网络游戏服务器, 两个线程, 一个线程保存玩家的命令到 队列, 一个线程从队列取出命令 并解析执行
//  
// 保护共享数据， 某个线程把共享数据锁住、操作、解锁
// 互斥量： 是个类对象，多个线程尝试用lock()成员函数来加锁 数据， 但只有一个线程能锁成功 
//          如果没有锁成功，那就卡在这里不断尝试加锁 数据
//      std:mutex mymutex; mymutex.lock();  mymutex.unlock();
//      先lock() 操作数据 后unlock()
//          lock() 和 unlock() 必须成对使用, 不是简单的数量上的成对， 指逻辑上的成对，有lock必须有对应的unlock（是个坑坑坑）
//      c++也有取代lock和unlock的方法，std::lock_guard类模板, std::lock_guard<std::mutex> myguard(mymutex);
//          std::lock_guard的原理， 在std::lock_guard的构造函数中 执行了 std::mutex::lock(); 
//          在其析构函数中执行std::mutex::unlock();
//          可以在 {} 中写std::lock_guard<std::mutex> myguard(mymutex); 生命周期就是 {}
//          听说std::lock_guard是为了防止 lock()之后unlock()之前程序异常。。。

//  死锁： 08春晚，林永健。 你不给打开箱子我就不给你证件，你不给证件我就不给你打开箱子 （证件锁在箱子里）
//      A、B两个线程，在A线程里有a、b两把锁需要依次先锁后开（两个线程加锁顺序相反）
//                   在B线程里有b、a两把锁需要依次先锁后开
//          问题是现在执行A锁上了a，操作系统发生上下文切换，去执行B锁上了b，
//          在B中马上要去锁a锁不住，到了A中锁b也锁不住，双方死等。
//      所以死锁产生的条件 至少需要两个线程，恰好上下文切换。
//      解决死锁： 1.两个线程加锁顺序相同。
// std::lock() 函数模板，处理多个互斥量才能用
//      能力: 一次锁住两个或以上互斥量（至少两个），不会因为锁的顺序导致死锁问题，不会出现互锁问题。
//      要么两个互斥量都锁住了，要么两个都没锁住。
//      基本原理：如果在一个线程中锁了一个量但锁不住第二个量，那么释放第一个量，隔段时间再锁两个量，保证都锁上。
//      std::lock(mymutex1, mymutex2);  相当于两个都.lock()
//      ... （被锁的东西）
//      mymutex1.unlock(); mymutex2.unlock(); 配合使用, 还是要对应，对应于上面std::lock()
//      上面三行这种用法还是要考虑unlock()的位置要与std::lock()所在的逻辑要对应
//  
//   std::lock(mymutex1, mymutex2); 
//   ... （被锁的东西）
//   std::lock_guard<std::mutex> myguard1(mymutex1, std::adopt_lock); // 在std::lock()之后。用adopt_lock保证在构造guard对象时不调用mutex的lock()
//   std::lock_guard<std::mutex> myguard2(mymutex2, std::adopt_lock); // 析构时自动unlock
//    ***std::adopt_lock是个结构体对象，起标记作用，表示该互斥量已经lock(), 所以前面必须lock否则没有用
// 
// unique_lock跟lock_guard类似 
// unique_lock的第二个参数
//  unique_lock取代lock_quard
//      unique_lock是个类模板，一般lock_guard推荐使用较为广泛，lock_guard取代了mutex的lock和unlock
//      unique_lock比lock_guard灵活很多，效率差一点，内存占用多一点
//      常规使用跟lock_guard一样，第二个参数也可以是std::adopt_lock, 含义一样，就是不再unique_lock的构造函数中调用mutex的lock()，前面必须lock否则无用
//          mymutex1.lock(); // （要先lock)
//          std::unique_lock<std::mutex> myuniquelock(mymutex1, std::adopt_lock); // 再std::adopt_lock   
//    ***std::try_to_lock, 第二个参数也可以是这个， 为了解决一个线程中执行时间很长，另个线程必须等待的问题
//      尝试用mutex的lock()去锁定这个mutex，如果没有锁定成功，也会立即返回不会阻塞。可以做其他事。
//      std::unique_lock<std::mutex> myuniquelock(mymutex1, std::try_to_lock); // 尝试去锁，不能锁返回，不会阻塞在这里
//      使用方法：（之前不能自己lock）
//          std::unique_lock<std::mutex> myuniquelock(mymutex1, std::try_to_lock);
//          if(myuniquelock.own_lock()) // 如果锁定成功 
//          {
                // 操作数据
                // 其他处理代码
//          }
//          else // 没有锁定成功
//          {
//              // 就算没有拿到锁，但是不阻塞，可以干点别的事
//          }
//    ***std::defer_lock, 初始化了一个没有加锁的mutex，
//      使用方法：（之前不能自己lock）
//      
// unique_lock的成员函数
//    （1）lock()
//    （2）unlock()
//     std::unique_lock<std::mutex> myuniquelock(mymutex1, std::defer_lock); // 将mymutex和myuniquelock绑定
//     myuiquelock.lock(); // 加锁，不用自己unlock，也可以自己unlock , 析构时自动unlock
//     // 处理共享代码, 数据
//     myuniquelock.unlock(); // 临时放开
//     // 处理非共享代码，，。。
//     myuniquelock.lock(); // 很灵活，可以随时加锁解锁
//    （3) try_lock(), 尝试给互斥量加锁，lock成功返回true ，否则返回false。 不阻塞
//    （4） release(), 返回它所管理的mutex对象指针，并释放所有权， 也就是说，这个unique_lock和mutex不再有联系
//          std::unique_lock<std::mutex> myuniquelock(mymutex1); // 绑定 并 lock
//          std::mutex* ptr = myuniquelock.release(); // 接管mutex，与unique_lock解除关系
//          // ....
//          ptr->unlock(); // 接管过来后有义务解锁，否则出错
// 
// unique_lock所有权的传递 mutex
//      一个mutex逻辑上只能属于一个unique_lock, 否则会逻辑混乱
//      但是所有权可以转移，不能复制，只是同一时间只属于一个unique_lock
//      像独占型智能指针，只能移动不能复制
//      std::unique_lock<std::mutex> myuniquelock1(mymutex1); // 绑定
//      std::unique_lock<std::mutex> myuniquelock2(mymutex1); // 绑定到另一个，语法没有问题，但是在构造函数中会调用两次lock(),导致一直等待，没有意义
//      std::unique_lock<std::mutex> myuniquelock2(myuniquelock1); // 不能复制，语法都会不过
//      std::unique_lock<std::mutex> myuniquelock2(std::move(myuniquelock1)); // 左值转右值，调用移动构造函数。 mymutex1与myuniquelock2绑定，与myunqlk1解除绑定
//    返回局部对象转移所有权
//      std::unique_lock<std::mutex> ret_unique_lock()
//      {
//          std::unique_lock<std::mutex> temp_uniquelock(myMutex); // 局部对象 temp_uniquelock
//          return temp_uniquelock; // 返回局部对象，导致系统生成临时对象，并调用unique_lock的移动构造函数
//      }
//      std::unique_lock<std::mutex> uniquelock = ret_unique_lock(); // uniquelock有了myMutex的所有权，
// 
// 
// 线程锁的粒度（锁住的代码有多少），用粗细表示
//    （1）锁住的代码越少，粒度越细，执行效率越高
//    （2）锁住的代码越多，粒度越粗，执行效率越低
//     要选择合适粒度的代码来保护，太细容易漏掉需要保护的数据，太粗效率低。
// 

// void print(vector<int> vctr)
// {
//     if(vctr.size() > 0)
//     for(auto v : vctr)
//         cout << v << " ";
//     cout << endl;
// }

class A
{
public:
    void capCmd()
    {
        for(int i=0; i<1000; i++)
        {
            myMutex.lock();
            cmdQueue.push_back(i);
            myMutex.unlock();
            cout << "push command is: " << i << endl;
        }
    }
    void exeCmd()
    {
        for(int i=0; i<1000; i++)
        {   
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
        }
    }
    std::unique_lock<std::mutex> ret_unique_lock()
    {
        std::unique_lock<std::mutex> temp_uniquelock(myMutex); // 局部对象 temp_uniquelock
        return temp_uniquelock; // 返回局部对象，导致系统生成临时对象，并调用unique_lock的移动构造函数
    }
private:
    list<int> cmdQueue;
    std::mutex myMutex; // 创建一个互斥量
};

int main()
{
    // vector<thread> threadVec;
    // vector<int> nums{1,2,3,4,5};
    // for(int i=0; i<10; i++)
    // {
    //     threadVec.push_back(thread(print, nums));
    // }
    // for(auto it=threadVec.begin(); it!=threadVec.end(); it++)
    // {
    //     it->join();
    // }
    
    A a;
    std::thread mythread1(&A::capCmd, &a);
    std::thread mythread2(&A::exeCmd, &a);
    mythread1.join();
    mythread2.join();

    return 0;
}