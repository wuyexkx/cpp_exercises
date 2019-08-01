#include <iostream>
#include <bitset>
using namespace std;

// ------------------------------这种写法必须并存------------------------------------
// 如果不写这个无参数的函数,将报错,error: no matching function for call to ‘print()’
// 因为递归到最后,后面的一包参数为空,传入的参数就是空,必须有函数与之对应
void print() { } 
// 模板参数为一个T 和一包Types  注意"..."的位置用法
template<typename T, typename... Types>
void print(const T& firstArg, const Types&... args)
{
    cout << sizeof...(args) << " "; // 通过sizeof...可以知道后面pack参数的个数
    cout << firstArg << endl; // 输出第一个参数
    print(args...); // 递归, 第一次到这里会把参数分为 1个 和 一小包, 一直分到最后传入参数为空 去调用那个空参数函数
}
// --------------------------------------------------------------------------------

int main()
{
    print(7.5, "hello!", bitset<16>(15), 100); // bitset类一定重载了<<操作符
    return 0;

    // output:
    // 7.5
    // hello!
    // 0000000000001111
    // 100
}