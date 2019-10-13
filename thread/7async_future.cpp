#include <iostream>
#include <thread>
#include <mutex>
#include <list>
#include <string>
#include <future>
#include <map>
#include <vector>
using namespace std;


int threadF()
{
    cout << "  thread id: " << std::this_thread::get_id() << endl;
    std::chrono::milliseconds dur(2000);
    std::this_thread::sleep_for(dur);
    cout << "thread over." << endl;
    return 5;
}

int threadF1(int i)
{
    cout << "  thread id: " << std::this_thread::get_id() << endl;
    std::chrono::milliseconds dur(2000);
    std::this_thread::sleep_for(dur);
    cout << "        arg: " << i << endl;
    return i;
}

// 在里边执行较长时间代码
void threadF2(std::promise<int>& temp, int calc) // 赋值给promise的类型为int
{
    std::chrono::milliseconds dur(2000);
    std::this_thread::sleep_for(dur);

    int result = calc * 999;
    // 最终结果保存
    temp.set_value(result); // 将结果保存到promise对象
}
void threadF3(std::future<int>& tempf)
{
    cout << "thread print: " << tempf.get() << endl;
}

int main()
{   // 课程P10 https://www.bilibili.com/video/av49288732/?p=10
    // 一.std::async, std::future创建后台任务并返回 (asynchronous异步, synchron同步)
    // 希望线程返回一个结果
    // std::async 是个函数模板(模板参数为任意返回值类型), 用来启动一个异步任务,启动起来一个异步任务, 之后返回std::future对象
    // "启动一个异步任务",自动创建一个线程并开始执行对应的入口函数, 返回一个std::future对象
        // 在std::future这个对象里边就含有 入口函数的返回结果(也就是线程返回的结果),通过future的get()成员方法获得结果
        // 有称,std::future提供了一种异步操作结果的机制,返回的对象中在将来可以获取到结果
        // future.get()一直阻塞到线程返回, 不能多次调用,就一次
        // future.wait()等待线程结束,不返回结果
        // 可以传递参数,std::launch类型(enum类型),
            // a)std::launch::deferred,（推迟）。表示线程入口函数调用 被延迟到执行wait()或get()时才调用, 根本没有创建线程,都在主线程中执行的 
            // b)std::launch::async, 这是async的默认参数, 创建线程并执行
    cout << "main thread: " << std::this_thread::get_id() << endl;
    // std::future<int> result = std::async(threadF); // 创建完就开始执行线程, 流程继续往下不卡在这(在win下是创建了一个线程 id不同; 但在ubuntu中id相同)
    // std::future<int> result = std::async(&A::threadF, &a);
    // std::future<int> result = std::async(std::launch::deferred, threadF); // 若后面没有wait或get则线程都不会被创建
    // std::future<int> result = std::async(std::launch::async, threadF); // 第一个是默认参数, 这样写在ubuntu中会创建线程
    // cout << result.get() << endl; // 阻塞到这里,等待线程返回


    // // 二.std::packaged_task 打包任务,类模板,模板参数为callable. 包装各种callable,方便作为线程入口参数
    // //     // packaged_task的对象 本身也是callable
    // // std::packaged_task<int(int)> pkg_callable(threadF1); // 通过pkg_callable把threadF1包装起来, int(int)分别表示callable的返回值和参数 
    // // std::thread mythread(std::ref(pkg_callable), 12);    // 创建一个线程,入口函数为一个pkg_task对象, 入口参数为callable的参数
    // // mythread.join();
    // // std::future<int> result = pkg_callable.get_future(); // result保存着线程入口函数的返回值, pkg_task绑定到future
    // // cout << "future result: " << result.get() << endl;
    // // // pkg_callable(100); // 可以直接使用packaged_task对象.

    //     // 奇怪用法 
    // packaged_task<int(int)> pkgT1(threadF1);
    // vector<packaged_task<int(int)>> v_pkg_task; //  创建存放此类型的 容器
    // v_pkg_task.push_back(std::move(pkgT1));     // 移动语义, 之后pkgT1为空
    // auto it = v_pkg_task.begin(); // 取出
    // pkgT1 = std::move(*it);       // 移动语义
    // v_pkg_task.erase(it);         // 删除 
    // pkgT1(110);                   // 直接调用


    // 三.std::promise, 类模板 , 可以在某个线程中给他赋值,在另一个线程中取出
    std::promise<int> mypromise;
    std::thread mythread(threadF2, std::ref(mypromise), 99);
    mythread.join();
    // 相当于用future转换了一下promise,获取它的值
    std::future<int> result = mypromise.get_future(); // promise与future绑定,用于获取线程返回值,
    // auto rst = result.get(); // get只能调用一次
    std::thread mythread1(threadF3, std::ref(result)); // 在上面线程中计算得到的结果到这个线程中打印
    mythread1.join();
    // cout << "rst: " << rst << endl;

    return 0;
}

