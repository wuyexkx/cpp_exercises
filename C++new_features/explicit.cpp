#include <iostream>

using namespace std;

template<typename T>
struct Complex
{
    Complex() { }
    explicit // 告诉编译器这个constuctor需要明确调用, 不要给我自动隐式转换
    Complex(const T r, const T i=0)
    : re(r), im(i) { }
    Complex operator+ (const Complex<T>& c)
    {
        return Complex<T>(re + c.re, im + c.im);
    }
    void show() const
    { std::cout << "(" << re << ", " << im << ")" << std::endl; }
private:
    T re;
    T im;
};


template<typename T>
struct P
{
public:
    explicit
    P(int a, int b) { cout << "P(int a, int b)" << endl; }                    // (1)
    P(initializer_list<int>) { cout << "P(initailizer_list<int>)" << endl; }  // (2)
    P(int a, int b, int c) { cout << "P(int a, int b, int c)" << endl; }      // (3)
};


int main()
{
    Complex<int> c1(1,0); c1.show();
    Complex<int> c2(2,0); c2.show();
    cout << endl;
    Complex<int> c3 = c1 + c2; 
    c3.show();
    // 旧版版本 non explicit---one argument 的 constuctor才可以做隐式转换
    // c1+2, c1是Complex类型,+的右边也是Complex类型,但这里不是,编译器把2自动转换成2 0i, 如果explcit,不会隐式转换
    Complex<int> c4; 
    // 加了explicit, 2 不会被隐式转换成Complex类型
    // c4 = c1 + 2; // error: no match for ‘operator+’ (operand types are ‘Complex<int>’ and ‘int’) 
    c4.show();
    // 加了explicit, 在构造c5时,12不会被隐式转换,  不加就被隐式转换
    // Complex<int> c5 = 12; // error: conversion from ‘int’ to non-scalar type ‘Complex<int>’ requested

    cout << endl;
    P<int> p1(77, 5);
    P<int> p1(77, 5);

    P<int> p2{77, 55};
    P<int> p6 = {77, 55};

    P<int> p3{77, 5, 42};
    P<int> p4(77, 5, 42);
    P<int> p5 = {77, 5, 42};

// output:
        // (1, 0)
        // (2, 0)

        // (3, 0)
        // (2, 0)

        // P(int a, int b)
        // P(initailizer_list<int>)
        // P(initailizer_list<int>)
        // P(initailizer_list<int>)
        // P(int a, int b, int c)
        // P(initailizer_list<int>)

    return 0;
}

