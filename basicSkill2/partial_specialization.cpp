#include <iostream>
using namespace std;

// 模板偏特化(局部特化),分两种情况, 1.个数上的偏; 2.范围上的偏


// 1. 模板参数个数偏
// 模板参数有两个, 第一个被绑定为bool型
// 先写接收任意类型的
template<typename T1, typename T2> 
class vector { };
// 再写偏特化版本的
template<typename T2>  
class vector<bool, T2> { };


// 2. 范围上偏 ,两个类模板本来就是完全独立
template<typename T> // 先写接收任意类型的
class C { public: C(){cout << "T" << endl;} };
template<typename U> // 再写偏特化版本的, 由任意类型缩小为指针类型 换成U也可以,本来就是完全独立
class C<U*> { public: C(){cout << "T*" << endl;} }; 


int main()
{
    C<string> c1; // 指定第一个 输出 T
    C<string*> c2; // 指定第二个 输出T*

    return 0;
}

