#include <iostream>
#include <deque>
#include <ctime>
#include <cstdio>
#include <string>
#include <stdexcept>
#include <algorithm>
using namespace std;

// 双向队列， 内存分段连续的，表面上是全部连续的
//  stack和queue底层都是直接用deque实现，并没有自己实现一种数据结构。
//  所以stack和queue在技术上叫 容器适配器（container adapter），表面上是个容器
//  stack和queue不提供iterator和find，等等，不能去操作中间的元素，只能按照这种特殊数据结构去使用
string get_a_targetStrings()
{
long target = 0;
char buf[10];
    cout << "target (0~" << RAND_MAX << "): ";
    cin >> target;
    snprintf(buf, 10, "%d", target);
    return string(buf);
}

void deque_test(long& value)
{
deque<string> dq;
char buf[10];
clock_t timeStart = clock();
    for(long i=0; i<value; ++i)
    {
        try
        {
            snprintf(buf, 10, "%d", rand());
            dq.push_back(string(buf));
        }
        catch(exception& p)
        {
            cout << "i=" << i << " " << p.what() << endl;
        }
    }
    cout << "      push time: " << clock() - timeStart << " ms" << endl;
    cout << "     deque.size: " << dq.size() << endl;
    cout << "    deque.front: " << dq.front() << endl;
    cout << "deque.max__size: " << dq.max_size() << endl;
    cout << "     deque.back: " << dq.back() << endl;

    timeStart = clock();
    // deque没有自带的sort，使用全局的
    ::sort(dq.begin(), dq.end());
    cout << "    ::sort time: " << clock() - timeStart << " ms" << endl;

    // deque没有自带的查找函数，使用全局的
string target = get_a_targetStrings();
    timeStart = clock();
auto pItem = ::find(dq.begin(), dq.end(), target);
    if(pItem != dq.end())
        cout << "          ::find: " << *pItem << endl;    
    else
        cout << "not find." << endl;
        cout << "     ::find time: " << clock() - timeStart << " ms" << endl;
}


int main()
{
    long num = 5000000;
    deque_test(num);
    return 0;
}
