#include <iostream>

using namespace std;

// 单例模式,所使用的类只希望创建一个对象

//------------第一种实现方法，早已存在（饿汉模式）---------------
class A
{
public:
    static A& getInstance() { return a; }   // 始终返回返回唯一A的对象a
    void f() { cout << "A::f()" << endl; } // 外部调用f，A::getInstance().f();
// 构造函数和拷贝构造函数放在private中，外界无法使用，只能在类内部使用，所以外界无法创建对象。
// 只能通过内部创建一个唯一对象返回出去。
private:
    A() { } // 定义构造函数
    A(const A& rhs) { }
    static A a; // 无人创建A的对象时，a已存在,有且只有一个对象a
};
// 定义唯一对象a，因为a在private中声明，但是没有定义，
// 不加这句会报错error: undefined reference to `A::a'
A A::a; 


//------------第二种实现方法，调用才存在（饱汉模式）---------------
class B
{
public:
    static B& getInstance();
    void f() { cout << "B::f()" << endl; }
// 构造函数和拷贝构造函数放在private中，外界无法使用，只能在类内部使用，所以外界无法创建对象。
private:
    B() { }
    B(const B& rhs) { }
};
B& B::getInstance()
{
    // 有调用时才会存在这个对象，且只创建一次，一直存在。
    static B b;
    return b;
}

int main()
{
    //  A::getInstance()是A的单例，A::getInstance().f()是调用此单例的成员函数
    A::getInstance().f(); 
    B::getInstance().f(); 

    return 0;
}
