#include <iostream>
#include "double_list.h"

using namespace std;

// 双向链表，添加 删除节点

int main()
{
    double_list<int> dl;
    dl.push_front(1);
    dl.push_front(2);
    dl.push_front(4);

    dl.print();
    dl.Delete(2);
    dl.Delete(4);
    dl.print();

    dl.push_front(6);
    dl.push_front(7);
    dl.print();
    dl.Delete(6);
    dl.print();

    // output:
        // 4 -> 2 -> 1
        // 1
        // 7 -> 6 -> 1
        // 7 -> 1

    return 0;
}