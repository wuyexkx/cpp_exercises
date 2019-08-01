#include <iostream>
#include <vector>
using namespace std;

// 1. reference 初始化之后不可再代表别的引用, 已经绑定到初始化的变量,,而指针可以变
// 2. sizeof(r)==sizeof(x) 变量多大,reference就有多大,尽管是编译器制造的假象假象.(reference底层是指针实现,32位中永远占4个字节)
// 3. 变量的地址==引用的地址

// 主要用于参数传递,(函数参数 函数返回值等等)


/*
// 以下被视为 "same signature" 函数签名相同 (所以二者不能同时存在)
// 返回值不属于函数签名
double    imag(const double& im) { }
double    imag(const double  im) { } // 调用时 ambiguity 如: imag(a) 不知道调用哪一个

// 以下可以共存, const属于签名的一部分
double    imag(const double& im) const { }
double    imag(const double  im) { } 
 */

int main()
{

    return 0;
}
