#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>

using namespace std;

// STL六大部件
//  容器(containers)
//  分配器(allocators)
//  算法(algorithm)
//  迭代器(iterator)
//  适配器(adapter)
//  仿函数(functor)

int main()
{
    int a[6] = {2, 32, 12, 43, 41, 0};
    vector<int, allocator<int>> v(a, a+6);
    // 满足条件计数, less为function object, bund2nd为function adapter(binder) not1为function adapter(negafor)
    // count_if是algorithm.  not1(bind2nd(less<int>(), 40))返回true or false
    cout << count_if(v.begin(), v.end(), 
            not1(bind2nd( less<int>(), 40) )) << endl; // 绑定参数, 绑定第二个参数 >=40


    return 0;
}
