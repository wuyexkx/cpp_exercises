#include <iostream>
#include "operator_overloading.h"

using namespace std;

// operator-overloading-1 (成员函数中)

// 关键字inline 必须与函数定义体放在一起才能使函数成为内联，仅将inline 放在函数声明前面不起任何作用。
// 所以说，inline 是一种“用于实现的关键字”，而不是一种“用于声明的关键字”。
// 体现了高质量C++/C 程序设计风格的一个基本原则：
// 声明与定义不可混为一谈，用户没有必要、也不应该知道函数是否需要内联。

