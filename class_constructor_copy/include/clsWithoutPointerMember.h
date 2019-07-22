#ifndef __COMPLEX__
#define __COMPLEX__

#include <iostream>
#include <string>
using namespace std;

// 前置声明,防止类的深度耦合导致的相互编译不通过
// class complex;

//====================1. 操作赋重载-1，成员函数===========================
// 类声明
class complex
{
public:
    // 构造函数，参数r和i的值默认为0，用初始化列表为private数据赋值
    complex (double r = 0, double i = 0)
    : re(r), im(i)
    { }

    // 函数声明
    // 重载操作赋，一个complex对象 使用+= 可以加上另一个复数 值返回给本对象
    // 参数为const，不希望改变数据
    complex& operator += (const complex&);
    complex& operator -= (const complex&);
    double real() const { return re; }
    double imag() const { return im; }
    void show_complex(string name);

private:
    double re, im;  

// 声明友元，可以使用private数据
// 第一个参数为complex指针，
// 同一对象互为友元，可以访问private
friend complex& __doapl (complex* , const complex&);
friend complex& __doamns (complex* , const complex&);

};

// 关键字inline 必须与函数定义体放在一起才能使函数成为内联，仅将inline 放在函数声明前面不起任何作用。
// 所以说，inline 是一种“用于实现的关键字”，而不是一种“用于声明的关键字”。
// 体现了高质量C++/C 程序设计风格的一个基本原则：
// 声明与定义不可混为一谈，用户没有必要、也不应该知道函数是否需要内联。
inline complex& 
__doapl (complex* ths, const complex& r)
{
    ths->re += r.re;
    ths->im += r.im;
    return *ths; // 传入此对象的指针，返回此对象（不用关心接收是reference还是value）
}
inline complex&
__doamns (complex *ths, const complex& r)
{
    ths->re -= r.re;
    ths->im -= r.im;
    return *ths;
}
// 定义 重载操作符函数 += 右边不动，因为为成员函数，左边作为隐藏参数this传入
// 内敛函数在.h文件中定义。参数为一个complex对象
inline complex&
complex::operator += (const complex& r)
{
    // 对象的函数，可以使用this关键字 表示此对象的指针
    // 用此对象的实部和虚部对应加上 r对象的实部和虚部 结果保存在此对象并返回
    return __doapl(this, r); // this默认是给实例用，加上static关键字类也可以用
}
inline complex&
complex::operator -= (const complex& r)
{
    return __doamns(this, r);
}


//====================2. 操作赋重载-2，非成员函数===========================
// 返回复数的实虚部
inline double real(const complex& x)
{
    return x.real();
}
inline double imag(const complex& x)
{
    return x.imag();
}
// 共轭复数
inline complex
conj(const complex& x)
{
    return complex(x.real(), -x.imag());
}

// 重载 加法运算符，有两个操作对象 return = x + y
inline complex
operator + (const complex& x, const complex& y)
{
    // 返回临时对象
    return complex (x.real() + y.real(),
                    x.imag() + y.imag());
}
// return = x + 1.0
inline complex
operator + (const complex& x, double r)
{
    return complex(x.real() + r, x.imag());
}
// return = 1.0 + x
inline complex
operator + (double r, const complex& x)
{
    return complex(r + x.real(), x.imag());
}

// 重载 正号   return = +x
// inline complex& 如果返回引用，参数中的const将被去掉，编译不通过
inline complex
operator + (const complex& x)
{
    return x;
}
// 重载 负号  return = -x
inline complex 
operator - (const complex& x)
{
    return complex(-x.real(), -x.imag());
}

// 重载 ==   (x == y)
inline bool
operator == (const complex& x, const complex& y)
{
    return x.real() == y.real() 
        && x.imag() == y.imag();
}
// 重载 ==   (x == 1)
inline bool
operator == (const complex& x, double i)
{
    return x.real() == i
        && x.imag() == 0;
}
// 重载 ==   (1 == y)
inline bool
operator == (double i, const complex& x)
{
    return i == x.real()
        && 0 == x.imag();
}

// 重载 << 此符号只能在global函数中重载。操作符一定作用到左边。因为如果是成员函数，用法为cls << cout;
// cout << c;希望输出c的复数形式  （cout实参，os形参）
// 参数：第一参数和cout一个类型 都是ostream的对象，第二参数为一个复数
//      不能const。const ostream& os说明os不可变，但os作为输出接收者 每次<<都在改变os
// 返回值： 返回值可以为空,因为一次输出之后可以不用在管
//         但若 cout << c1 << c2;出错。 << c返回值为空。 （cout实参，os形参）
inline ostream&
operator << (ostream& os, const complex& x)
{
    return os << "(" << real(x) << ", " << imag(x) << ")\n";
}
// inline void
// operator << (ostream& os, const complex& x)
// {
//     os << "(" << real(x) << ", " << imag(x) << ")\n";
// }



#endif

// https://bbs.csdn.net/topics/240026824

