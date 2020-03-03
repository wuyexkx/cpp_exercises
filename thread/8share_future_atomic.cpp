#include <iostream>
#include <thread>
#include <future>
#include <mutex>
#include <atomic>

using namespace std;

// 一、二、三 用到
int thread_func()
{
    cout << "thread_func() start. threadid: " << std::this_thread::get_id() << endl;
    std::chrono::milliseconds dur(1500);
    std::this_thread::sleep_for(dur);
    cout << "thread_func() end. threadid: " << std::this_thread::get_id() << endl; 
    return 5;
}

// 四 用到
std::atomic<int> count1{0}; //  封装了一个类型为int的对象，操作跟int一样  count1=0;编译出错。
std::mutex mymutex;
int count = 0;
void thread_func1()
{
    for(int i=0; i<1000000; ++i)
    {
        // mymutex.lock(); // 如果不用互斥量加锁，最终计算结果不是理想值
        // ++count;
        // mymutex.unlock();
        ++count1; // 对count的操作是一个原子操作，不会被打断
    }
}


int main()
{
    // 一、future的wait_for()成员函数
        // 等待一定时间，返回enum对象，然后判断线程是否超时(timeout)、返回(ready)、延迟(deferred)
    // 二、std::future_status枚举类型，
    // 三、Note：
        // 为什么future对象只能get()一次，因为是用的移动语义，再次get()时就空了。可以用future的valid()成员函数判断是否为空，返回bool
        // 如果多个线程都要get()某个线程的值时就会出问题，，所以引入std::sgared_future
    // 四、std::shared_future类模板 （可以get多次，不是移动语义实现）
        // 可以多次get，可以实现在多个线程中获得线程的返回值
    // 五、原子操作std::atomic（类模板）原子操作只能操作单个变量
        // 可以理解成不需要互斥量的加锁的 多线程并发编程技术，比互斥量效率高（但互斥量可以锁很多代码，原子操作只能操作单个变量）
        // 原子操作：在多线程中不会被打断的程序片段 （原子指不可能被分割的代码，要么完成，要么没有完成，不存在中间状态） 
        // 一个线程读 一个线程写同一数据 也会出问题（感觉读的数据最多是没有更新，但实际可能读到不可预料的中间值）


    /********** 一、二、三
    cout << "main threadid: " << std::this_thread::get_id() << endl;
    std::future<int> futureObj = std::async(thread_func); // 创建新线程 并运行，继续往下执行
    // std::future<int> futureObj = std::async(std::launch::deferred, thread_func); // 创建新线程 延迟执行    
    cout << "continue..." << endl;
    // cout << "futureObj.get(): " << futureObj.get() << endl; // 阻塞到线程结束，得到线程返回值
    // 枚举类型：
    std::future_status status = futureObj.wait_for(std::chrono::seconds(2)); // 等待1秒，希望线程正常返回。但是线程需要1.5秒，所以超时
    if(status == std::future_status::timeout)    // 判断子线程线程超时，子线程还没有执行完
    {
        cout << "subthread time out." << endl;
    }
    else if(status == std::future_status::ready) // 判断线程成功返回
    {
        cout << "sub thread over. return success." << endl;
        cout << "whether get ? " << futureObj.valid() << endl;
        cout << "sub thread return: " << futureObj.get() << endl; // 线程成功结束返回，这样get不用阻塞等待了
        cout << "whether get ? " << futureObj.valid() << endl;
    }
    else if(status == std::future_status::deferred) // 如果async的第一个参数为std::launch::deferred则判断成立
    {
        cout << "subthread is defferd." << endl; // 线程被延时执行
        cout << "defferd execute: " << futureObj.get() << endl; // 延迟到这里执行，但是还是在主线程中执行的
    }
    cout << "over." << endl;
    **********/

    /********** 四
    std::future<int> futureObj = std::async(thread_func);
    // std::shared_future<int> shared_futureObj(std::move(futureObj)); // 只能接收右值
    std::shared_future<int> shared_futureObj(futureObj.share());
    // std::packaged_task<int()> myPkg(thread_func); // 包装起来         // 这两行get后，windows10运行卡住，不报错，
    // std::shared_future<int> shared_futureObj(myPkg.get_future()); // 视频（11集43分）里可以运行
    cout << shared_futureObj.get() << endl; // 返回5
    cout << shared_futureObj.get() << endl;
    **********/

   //********** 五
    std::thread mythread1(thread_func1);
    std::thread mythread2(thread_func1);
    mythread1.join();
    mythread2.join();
    // cout << "count: " << count << endl;
    cout << "count: " << count1 << endl;


    return 0;
}

