#include <iostream>
#include "loop_list.h"
using namespace std;

// 单向循环链表
// 有表头，多出一个空节点，新节点一次往后添加
//      约瑟夫问题会用到循环链表结构


int main()
{

    loop_list<int> l;
    l.Insert(10);
    l.Insert(11);
    l.Insert(12);

    l.Print();
    l.Delete(10);
    l.Print();
    l.Insert(13);
    l.Delete(11);
    l.Print();

    // output:
        // 12 -> 11 -> 10
        // 12 -> 11
        // 13 -> 12

    return 0;
}
