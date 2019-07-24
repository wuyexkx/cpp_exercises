#ifndef __TEMPLATE__
#define __TEMPLATE__

#include <iostream>
using namespace std;

// 代码膨胀有必要
// -------------------1.类模板-----------------------
template<typename T>
class complex
{
public:
    complex(T r = 0, T i = 0)
    : re (r), im (i) 
    { }
    complex<T>& operator += (const complex<T>&);
    T real() { return re; }
    T imag() { return im; }
private:
    T re, im;
    // friend complex<T>& __doapl(complex<T>*, const complex<T>&);
};
// template<typename T>
// inline complex<T>&  
// __doapl(complex<T>* ths, const complex<T>& x)
// {
//     ths->re += x.re;
//     ths->im += x.im;
//     return *ths;
// }
template<typename T>
inline complex<T>& 
complex<T>::operator += (const complex<T>& x)
{
    this->re += x.re;
    this->im += x.im;
    return *this;
    // return __doapl(this, x);
}
// -------------------------------------------------



class stone
{
public:
    stone(int w = 0, int h = 0, int weight = 0)
    : _w(w), _h(h), _weight(weight)
    { }
    bool operator< (const stone& rhs) const
        { return _weight < rhs._weight; } // this->_weight和rhs._weight比较
    int get_weight(){ return _weight; }
private:
    int _w, _h, _weight;
};
// -------------------2.函数模板-----------------------
//  函数模板，在使用时，编译器会对 函数模板 进行 参数推导(argument deduction)
//  1. T& min(const T& a, const T& b)
//       error: call of overloaded 'min(stone&, stone&)' is ambiguous(含糊不清)
//       solution：因为使用了using namespace std; std包含min
//  2. T& mini(const T& a, const T& b)
//       error: binding reference of type 'stone&' to 'const stone' discards qualifiers
//              (“stone&”类型的引用绑定到“const stone”丢弃限定符)
//       solution：传入的a,b本为不可变，函数返回值为非const的引用，
//                 也就是说T&绑定到了const T&，函数外部可能对其修改，与传入的限定冲突。
template<class T>
const T& mini(const T& a, const T& b)
{
    // 两个stone比较大小，需要在stone类中进行操作符重载
    // 各司其职，责任分明，c++标准库algorithm中大量使用函数模板
    return a < b ? a : b;
}

#endif
