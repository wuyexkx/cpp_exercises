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
//      容器结构分类： sequence associative unordered
//      sequence： array vector deque  list forward-list  
//      associative： set/multiset（只有value）  map/multimap(key-value) （用于大量查找，红黑树， multi是可重复的）
//          unodered： unordered set/multiset unordered map/multimap 
//                      （hash table[separate chaining最好的实现方法，可以碰撞，但是碰撞次数太多造成链表太长，查找很慢]）

int main()
{
    int a[6] = {2, 32, 12, 43, 41, 0};
    vector<int, allocator<int>> v(a, a+6);
    // 满足条件计数, less为function object, bund2nd为function adapter(binder) not1为function adapter(negafor)
    // count_if是algorithm.  not1(bind2nd(less<int>(), 40))返回true or false 也就是>=40的数为true
    cout << count_if(v.begin(), v.end(), 
            not1(bind2nd( less<int>(), 40) )) << endl; // 绑定参数, 绑定第二个参数 >=40

    return 0;
}
