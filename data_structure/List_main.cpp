#include <iostream>
#include "List.h"
using namespace std;

int main()
{
    List<int> L;
    L.Insert(0);
    L.Insert(1);
    L.Insert(2);
    L.Insert(3);
    L.Insert(4);
    L.show();

    L.Delete(2); // 删除中间
    L.show();
    L.Delete(4); // 删除第一个
    L.show();
    L.Delete(20);// 删除没有的
    L.show();

    L.Invert();
    L.show();

    return 0;
}