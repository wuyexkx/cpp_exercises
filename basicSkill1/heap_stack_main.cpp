#include <iostream>
#include "clsWithPointerMember.h"

/* stack(栈) and heap(堆) and 生命期
--Stack: 是存在于某作用域(scope)的一块内存空间(memory space)。
    例如当你调用函数，函数本身即会形成一个stack用来放置它所接收的参数，以及返回地址。
    在函数体内声明的变量，其所使用的内存块都取自上述stack。
    作用域内的对象，称为stack object or auto object, 会被自动清理
    {
        ...
    }


--Heap: 是指操作系统提供的一块global内存空间，程序可以动态分配从中获得若干区块。


---static local objects的生命期
   ex：
    {
        static complex c2(1, 2);
    }
    c2为static obj，其生命在作用域结束之后仍然存在，直到整个程序结束。但只有local可见。


---global object的生命期
    作用域之外的对象为全局对象。如c2
    可以视为一种static obj，其作用域是整个程序。其生命在整个程序结束后才结束。
   ex:
    complex c2(1,3);
    int main()
    {
        ...
    }


---heap object的生命期
    p1和p2所指的都是heap obj，p1所指空间生命在delete时结束；
    p2在作用域完时结束，但p2所指heap obj仍然存在。作用域之外再也不见p2，再也无法delete p2。内存泄漏。
   ex1：                              ex2:
    {                                  {+
        complex* p1 = new complex;         complex* p2 = complex;
        ...                            }
        delete p1; 
    }
    内存泄漏：申请的内存空间，在经过某些时间或作用域之后，对其失去控制，以至于无法归还给操作系统。

 */


// class的static类型
// static数据，
//      不属于对象私有。创建多个对象但static只创建一次。对象可以修改它。
//      由Account创建的所有对象共用static数据，一改全改
//      ex：银行账户，可以创建多个客户，但利率都一样的，利率可以设计成static类型。
// 
// static函数，
// 没有隐形参数 this指针。所以只能处理static的数据。而成员函数默认包含this,调用数据时没写this编译器会自动加上。
// static属于类和成员，可以通过两种方法调用：
//                  1.通过类名调用 Account::set_rate(); 
//                  2.通过对象调用 Account a; a.set_rate(); 

class Account
{
public:
    static double m_rate; // 声明类里有一个变量m_rate为static类型, 脱离对象，只在对象中声明
    static void set_rate(const double& x) { m_rate = x; }
    void show_rate() { cout << "Account rate: " << m_rate << endl;}
private:
    int balance;
};
//  static数据脱离对象存在，只在对象中声明静态数据。所以需要在类外加上定义，可以不赋初值。
// 定义，使变量获得内存的操作叫定义
// static数据不属于对象
double Account::m_rate = 8.0; 


int main()
{
    Account::set_rate(5.0); // className::staticFunction
    Account::m_rate = 4;    // objName::staticData
    cout << Account::m_rate << endl;
    Account a;
    a.show_rate(); // objName.staticFunction
    a.m_rate = 1;  // objName.staticData
    a.show_rate();
    Account aa;
    aa.show_rate();

    return 0;
}
