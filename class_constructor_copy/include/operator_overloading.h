#ifndef __COMPLEX__
#define __COMPLEX__

// 前置声明
class complex;

// 类声明
class complex
{
public:
    complex (double r = 0, double i = 0)
    : re(r), im(i)
    { }
    complex& operator += (const complex&);
    double real() const { return re; }
    double imag() const { return im; }

private:
    double re, im;  

friend complex& __doapl (complex* , const complex&);

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
    return *ths;
}
inline complex&
complex::operator += (const complex& r)
{
    return __doapl(this, r); // this默认是给实例用，加上static关键字类也可以用
}


#endif

// https://bbs.csdn.net/topics/240026824