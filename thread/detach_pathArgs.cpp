#include <iostream>
#include <thread>
using namespace std;

// 使用detach(), 有很多陷进, 使用主线程中的对象来构造时 容易出错
// 传入指针, 绝对有安全隐患, 在主程序结束时, 指针所指的对象消失, 再使用这个指针很危险
// 传入引用, 没有用, 就是值传递, 必须通过std::ref(a)才是引用传递

class A
{
public:
    A(const int i=12): data(i) 
    { 
        cout << "A constructor.\n"; 
        cout << "     thread id: " << this_thread::get_id() << endl;
    }
    A(const A& a) 
    { 
        cout << "A copy constructor.\n"; 
        cout << "     thread id: " << this_thread::get_id() << endl;
    }
    void show(int j=0) const
    { 
        cout << "show arg: "<< j << endl; 
    }
private:
    int data;
};
// void print(const int& i, char* pmybuf)
// void print(const int& i, string& pmybuf) // 在子线程中构造完成 隐患, 在主程序完毕后,可能对象还没有构造出来
// void print(const int& i, string(pmybuf)) // 在主线程中构造完成
// 创建线程时,这样调用thread th(print, i, A(a));
// 在主线程中构造完成, A& a会调用一次构造函数, 两次拷贝构造函数. 
//                   A a会调用一次构造函数, 三次拷贝构造函数.
void print(const int& i, const A& a) 
{
    cout << i << endl;
    a.show();
    cout << " sub thread id: " << this_thread::get_id() << endl;
}


int main()
{
    cout << "main thread id: " << this_thread::get_id() << endl;

    int i = 8;
    // char* s = "fdfdf";
    // thread mythread1(print, 5, i); // i会被隐式转换成A类型的临时对象, 但是在 子 线程中调用一次构造
    thread mythread1(print, 5, A(i)); // A(i)这种方式是 在 主 线程中构造, 推荐使用
    mythread1.join();
    // mythread1.detach();
    cout << "===================\n";
    A a;
    cout << "===================\n";
    thread mythread2(&A::show, &a, 10); // 用成员函数
    // thread mythread2(&A::show, a, 10); // 

    mythread2.join();

    return 0;
}
