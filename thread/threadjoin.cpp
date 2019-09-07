#include <iostream>
#include <thread>
using namespace std;

void print()
{
    cout << "sub thread starting...\n";
    cout << "sub thread end.\n";
}
class A
{
public:
    A() { }
    A(const A& a) { cout << "A copy constructor.\n"; }
    ~A() { cout << "A destructor.\n";}
    void operator()() const { cout << "class A subthread.\n"; }
};
// thread(obj) obj为可调用对象，函数、仿函数等
// join() 汇合，阻塞主线程，等待子线程结束
//      主线程执行完毕，但是子线程没有执行完毕，程序不合格，不稳定。
// detach() 分离， 子线程不和主线程汇合，主线程不等子线程，也不影响子线程执行。
//      一旦detach之后，与主线程关联的子线程对象 就会与 这个主线程失联，子线程驻留在后台运行，
//      由c++运行时库接管，运行结束后，运行时库负责清理相关资源（守护线程）。
//      detach使mythread线程失去自己控制。如果使用了detach就不能再join(), 否则系统异常。
//      引入detach的原因，让主线程逐个等待多个子线程结束方法不太好。但是还是建议等待。
// joinable() 判断是否可以使用join()或detach(); 返回true或false
// ---------------------------------------------------------------
// 二、其他创建线程的方法
//  1. 用类的对象（必须是可调用对象，重载() ）
//     thread th(a), a这个对象实际是被拷贝到子线程内部的，子线程结束，内部自动析构。
//     所以， 只要a中没有引用、指针，就不会出问题。
//  2. labmda

int main()
{
    cout << "main thread starting...\n";
    thread mythread(print); // thread 11标准库的类， 1. 创建mythread线程，线程入口是print() 2. mythread线程开始执行
    mythread.join(); // 阻塞主线程，让主线程等待子线程执行完毕，子主线程在这里汇合，然后继续往下执行 （防止混乱，不稳定）
    // mythread.detach();

    A a;
    thread mythread1(a); // 实际是拷贝的a到子线程内部去的
    mythread1.join();

    auto obj = [] ()
    {
        cout << "lambda starting...\n";
        cout << "lambda end.\n";
    };
    thread mythread2(obj);
    mythread2.join();

    cout << "main thread end.\n";

    return 0;
}
