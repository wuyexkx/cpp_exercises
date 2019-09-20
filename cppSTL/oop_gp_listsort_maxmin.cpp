#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

// oop 和 gp 的区别就是 data 和 method关系的区别
// oop 面向对象是把 数据和其操作方法组合到一起
// gp 将 数据 和 方法 分开，各自发展自己，通过iterator连接


// 为什么有的容器不能用全局的sort方法？
//   比如list，不能使用::sort(), 因为list底层是用链表实现，链表是通过各节点联系在一起的，内存空间不一定连续，
//   而全局的::sort()的底层实现是对迭代器进行了+ - * /等操作，只有RandomAccessIterator(随机访问迭代器)才能这些操作而不出错


// 所有algorithms，内部操作其实都是在比大小，==就是不大也不小
bool comp_strLong(const string& s1, const string& s2) // 比较规则
{
    return s1.size() < s2.size();
}

int main()
{
    cout << max(string("aaa"), string("bb")) << endl;
    cout << max(string("aaa"), string("bb"), comp_strLong) << endl;
    return 0;
}