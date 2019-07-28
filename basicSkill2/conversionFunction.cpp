#include <iostream>
#include <typeinfo>
using namespace std;

// 转换函数，将一个类的对象转换成另一种类的对象
// 转换函数没有返回类型，跟写的一样

class Fraction
{
public:
    // non-explicit-one-argument, two parameter one argument
    // 这样编译器可能将3替代为3/1来构造Fraction对象
    Fraction(int num, int den = 1)
    : m_numerator(num), m_denominator(den) { }
    // (转出)可以将Fraction对象转换为double。不需要参数，无返回类型（返回type跟double一致）
    operator double() const // 转换函数通常const
    {
        // 视频为double (m_numerator / m_denominator);先3,5整数相除取整得0，再将0转成double
        return (double) m_numerator / m_denominator; // 设计者 设计认为转换成合理的类型，具体怎么转换
    }
    Fraction operator+ (const Fraction& f)
    {
        return Fraction(m_numerator);
    }
private:
    int m_numerator;
    int m_denominator;
};

int main()
{
    Fraction f(3, 5);
    // // 在没有重载+的情况下，以下三行都是正确的
    // double b = 5 + f; // 调用operator double()将f转换成0.6
    // Fraction c = f + 4; // 没有重载+时，4会被non-explicit构造函数转换成Fraction型
    // Fraction c = 4 + f; // 没有重载+时，4会被non-explicit构造函数转换成Fraction型

    // 在重载+的情况下，第一行对，第二三行错，第四行对
    // error: ambiguous overload for 'operator+' (operand types are 'Fraction' and 'int')
    // double b = 5 + f; // f会被转换成double
    // double c = f + 5; // +右边变成Fraction，还是f变成double； ambiguous!!!!!!!!!!
    // Fraction c = f + 5; // +右边变成Fraction，还是f变成double； ambiguous!!!!!!!!!!
    // Fraction c = 3 + f;  // +右边为Fraction, 3会被转化成Fraction

    // 如果构造函数改为 explicit Fraction(int num, int den = 1)，重载+不变
    // 明确+两端都必须是Fraction，否则错误
    // Fraction c = f + 1; // error: conversion from 'double' to non-scalar type 'Fraction' requested
    // explicit基本只在构造函数这里用，还有就是template小地方会用到

    return 0;
}


