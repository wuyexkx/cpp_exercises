#ifndef __COMPLEX__
#define __COMPLEX__

// 前置声明,防止类的深度耦合导致的相互编译不通过
// class complex;


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
    // 参数为const，不希望改变它
    complex& operator += (const complex&);
    complex& operator -= (const complex&);
    double real() const { return re; }
    double imag() const { return im; }

private:
    double re, im;  

// 声明友元，可以使用private数据
// 第一个参数为complex指针，在
friend complex& __doapl (complex* , const complex&);
friend complex& __domns (complex* , const complex&);

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
__domns (complex *ths, const complex& r)
{
    ths->real -= r.re;
    ths->imag -= r.im;
    return *ths;
}
// 定义 重载操作符函数
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
    return __domns(this, r);
}

#endif

// https://bbs.csdn.net/topics/240026824


