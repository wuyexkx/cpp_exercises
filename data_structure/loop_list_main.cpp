#include <iostream>
#include "loop_list.h"

using namespace std;

// class ListNode  // 链表的一个节点
// {

// public:
//     // ListNode() { cout << "==============\n"; };
//     ListNode(int item = 10) // 构造函数 初始化data
//     : data(item) { };
// private:
//     int data; // 本节点所存储的数据
//     ListNode* link; // 连接到下一个节点的指针变量
// };


int main()
{

    loopList<int> l;
    l.Insert(10);
    l.Insert(11);
    l.Insert(12);

    // l.show();
    // l.Delete(10);
    l.show();

    loopList_Iterator<int> li(l);
    // cout << *li.First() << endl;
    // cout << *li.Next() << endl;
    // cout << *li.Next() << endl;
    // cout << *li.Next() << endl;
    // cout << *li.Next() << endl;
    // cout << *li.Next() << endl;
    cout << *li.First() << endl;
    // cout << *li.Next() << endl;
    // cout << *li.First() << endl;


    return 0;
}