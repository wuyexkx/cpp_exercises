#include <iostream>
using namespace std;


class A
{
public: 
    virtual void function1() { cout << "A::function1()\n"; }
    void function2() { cout << "A::function2()\n"; }
private:
    int a, b;
};

class B: public A
{
public:
    virtual void function1(int i) { cout << "B::function1()\n"; }
    void function3() { cout << "B::function3()\n"; }
private:
    int c, d;
};


int main()
{

    A* a ; // 定义指向A的指针

    B b; // 定义b对象
    // b.function1(1); // OK
    // b.A::function1(); // 显视调用父类的function1

    a = &b; // a指向了b的对象
    // a->function1(1);// ERROR 函数签名已变,并非重写父类的function1,,这是B自己的虚函数,所以A的虚表里没有,通过A的指针找不到它
    // a->function3(); // ERROR 虚表里没有这个函数的地址
    
    return 0;
}
