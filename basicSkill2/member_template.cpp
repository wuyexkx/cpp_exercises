#include <iostream>
#include <vector>
using namespace std;

// 模板主要分为三大类: class template   function template   member template


// 成员模板  类模板内包含成员函数也是模板函数
// 标准库的很多模板的构造函数都会设计成模板函数

template<class T1, class T2>
struct mypair
{
    typedef T1 first_type;
    typedef T2 second_type;

    T1 first;
    T2 second;

    // 构造函数
    mypair()
    : first(T1()), second(T2()) { }
    mypair(const T1& a, const T2& b) 
    : first(a), second(b) { }

    // 成员模板 // 拷贝构造函数
    template<class U1, class U2>
    mypair(const mypair<U1, U2>& p) 
    : first(p.first), second(p.second) { }
};

class Base1 { }; // 鸟类
class Base2 { }; // 鱼类
class Derived1 : public Base1 { }; // 麻雀
class Derived2 : public Base2 { }; // 鲫鱼


// 成员模板在智能指针上也有应用
// template<typename _Tp>
// class shared_ptr: public __shared_ptr<_Tp>
// {
//     template<typename _Tp1>
//     explicit shared_ptr(_Tp1* __p)
//     : __shared_ptr<_Tp>(__p) {}
// };

int main()
{
    mypair<Derived1, Derived2> p1;
    mypair<Base1, Base2> p2(p1); // 用子类对象去初始化构造父类对象, 调用拷贝构造函数  (麻雀是鸟类)
    // 拷贝构造函数里边有初始参数, 
    // mypair<Base1, Base2> p1;
    // mypair<Derived1, Derived2> p2(p1); // 用父类对象去初始化构造子类对象, 错误 (鸟类是麻雀)

    // 普通指针的功能如下,智能指针也应该有这种功能
    Base1 *ptr = new Derived1; // up-cast(向上造型) 把子类当做父类对象看待。指向父类的指针 可以指向 子类
    // 智能指针也应该有这种功能
    // shared_ptr<Base1> sptr(new Derived1);

    return 0;
}

