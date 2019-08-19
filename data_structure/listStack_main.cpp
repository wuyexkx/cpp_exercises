/*顺序栈: 用数组做的堆栈
    缺点: 插入删除速度慢,超容量时需要重新分配内存大小
  链式栈: 用链表做的堆栈
    优点: 插入删除速度很快
*/

#include <iostream>
#include "list_stack.h"
using namespace std;

int main()
{
    listStack<int> ls;
    ls.Push(10);
    cout << ls.Top() << endl;
    ls.Push(11);
    cout << ls.Top() << endl;
    ls.Push(12);
    cout << ls.Top() << endl;
    ls.Push(13);
    cout << ls.Top() << endl;
    ls.Push(14);
    cout << ls.Top() << endl;

    cout << "--------------------\n";
    ls.Pop();
    cout << ls.Top() << endl;
    ls.Pop();
    cout << ls.Top() << endl;
    ls.Pop();
    cout << ls.Top() << endl;


return 0;
}